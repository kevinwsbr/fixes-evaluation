 /*-------------------------------------------------------------------------*/

static int
dwg_write_entity (bit_out_t *dat, Dwg_Object *obj)
{
  // TODO: handle entities with extra data in their classes
  unsigned long start = dat->byte;
  BITCODE_BL size, end;
  int error;

  if (!obj) return 0;
#if defined(_DEBUG) && !defined(USE_TRACING)
  LOG_TRACE ("\n[%d] %s(%lx):\n", dat->opts & DWG_OPTS_FROM_OBJECTS ? obj->index : 0,
             dwg_class_name_str (obj->type), obj->handle.value);
#endif
  LOG_TRACE ("dwg_write_entity: " FORMAT_H ", %s\n", ARGS_H (obj->handle),
             dwg_class_name_str (obj->type));
  // TODO: handle unknown classes
  error = dwg_write_object (dat, obj);
  if (!error) return 0; // already printed
#if defined(LOGGING_LEVEL) && LOGGING_LEVEL < 4
  if ((obj->handle.value == 0) || (obj->type <= DWG_TYPE_TEXT)) // skip unknown
    {
      LOG_TRACE ("dwg_write_entity: SKIPPING\n");
      return error;
    }
#endif
  size = dat->byte - start;
  end = start + size;
  if (dat->opts & DWG_OPTS_IN) // write size and set end position
    {
      bit_write_BL (dat, size);
      end = dat->byte + size;
    }
  else if (size != obj->fixed_size)
    {
      LOG_WARN ("dwg_write_entity: wrong fixed size for %s, " FORMAT_BL " != "
                FORMAT_BL, dwg_class_name_str (obj->type), size,
                obj->fixed_size);
#if defined(LOGGING_LEVEL) && LOGGING_LEVEL < 4
      if ((obj->handle.value == 0) || (obj->type <= DWG_TYPE_TEXT)) // skip unknown
        {
          dat->byte = end;
          return error;
        }
#endif
    }
  LOG_TRACE ("dwg_write_entity: %d, size " FORMAT_BL " + " FORMAT_BL "\n",
             obj->type, start, size);
  if (dat->byte < end)
    bit_pad_filler (dat, end); // fill with zeros

  return error;
}
#define IS_ENCODER
#include "classes.inc"
#undef IS_ENCODER

/*-------------------------------------------------------------------------*/

int
dwg_write_entityset (bit_out_t *dat, Dwg_Data *dwg)
{
  int i;

  for (i = 0; i < dwg->num_objects; i++)
    {
      if (!dwg->object[i]) continue;
      if (!IS_ENTITY (dwg->object[i])) continue;
#if defined(LOGGING_LEVEL) && LOGGING_LEVEL >= 4
      dwg_write_entity (dat, dwg->object[i]);
#else
      if (dwg->object[i]->handle.value == 0) // skip unknown
        {
          LOG_TRACE ("dwg_write_entityset: SKIPPING %s\n",
                     dwg_class_name_str (dwg->object[i]->type));
#if defined(LOGGING_LEVEL) && LOGGING_LEVEL < 4
          continue; // skip
#else
        }
      else if (!IS_ENTITY (dwg->object[i]))
        {
          LOG_TRACE ("dwg_write_entityset: SKIPPING %s\n",
                     dwg_class_name_str (dwg->object[i]->type));
          continue; // skip
#endif
      }
      if (dwg->object[i]->fixed_size)
        {
          bit_write_BL (dat, dwg->object[i]->fixed_size);
          dwg_write_entity (dat, dwg->object[i]);
        }
#endif
    }
  LOG_TRACE ("dwg_write_entityset: end\n");
  return 0;
}

/*-------------------------------------------------------------------------*/

int
dwg_write_header (bit_out_t *dat, Dwg_Data *dwg)
{
  BITCODE_BL size, start = dat->byte;

#if defined(LOGGING_LEVEL) && LOGGING_LEVEL >= 3
  LOG_TRACE ("\nHeader:\n");
#endif
  bit_write_RC (dat, "AC1024", 6);
  size = 85;                        // constant
  bit_write_BL (dat, size);         // variable part size
  bit_write_BS (dat, dwg->version); // version
#if defined(LOGGING_LEVEL) && LOGGING_LEVEL >= 4
  if ((dwg->header.tio == 0x18) || (dwg->header.tio == 0x27))
    {
      bit_write_RC (dat, "\x00", 6); // tio?
      dat->byte -= 1;
    }
#endif
  if (dwg->version >= R_2004)
    bit_write_BS (dat, dwg->header.tio); // tio
  bit_write_H (dat, dwg->header.zero);   // zero handle
  bit_write_BL (dat, dwg->header.dsize); // dsize
  if (dwg->version >= R_2010)
    {
      bit_write_BS (dat, dwg->header.unknown);                   // unknown
      bit_write_RC (dat, &dwg->header.security_flags[3], 4);     // security flags
      bit_write_RC (dat, &dwg->header.security_flags[0], 2);     // ...
      bit_write_BL (dat, dwg->header.unknown_2);                 // unknown
      bit_write_RC (dat, &dwg->header.security_flags[6], 14 - 5); // ...
      dat->byte -= 7;
    }
  else if (dwg->version >= R_2007)
    {
      bit_write_BS (dat, dwg->header.unknown);                   // unknown
      bit_write_RC (dat, &dwg->header.security_flags[3], 4);     // security flags
      bit_write_RC (dat, &dwg->header.security_flags[0], 2);     // ...
      bit_write_BL (dat, dwg->header.unknown_2);                 // unknown
      dat->byte -= 7;
    }
  else if (dwg->version >= R_2004)
    {
      bit_write_BS (dat, dwg->header.unknown); // unknown
      dat->byte--;
    }
  bit_write_BL (dat, dwg->header.nums_handles);   // num handles
  bit_write_BL (dat, dwg->header.nums_classes);   // num classes
  if (dwg->version >= R_2010)
    {
      bit_write_H (dat, dwg->header.max_handles[3]);     // max handles
      bit_write_RC (dat, &dwg->header.max_handles[5], 8); // ...
      dat->byte -= 4;
    }
  else if (dwg->version >= R_2007)
    {
      bit_write_H (dat, dwg->header.max_handles[3]);     // max handles
      bit_write_RC (dat, &dwg->header.max_handles[5], 6); // ...
      dat->byte -= 4;
    }
  else if (dwg->version >= R_2004)
    {
      bit_write_H (dat, dwg->header.max_handles[3]);     // max handles
      bit_write_RC (dat, &dwg->header.max_handles[5], 6); // ...
      dat->byte--;
    }
  else if (dwg->version >= R_2000)
    {
      bit_write_H (dat, dwg->header.max_handles[3]);     // max handles
      bit_write_RC (dat, &dwg->header.max_handles[5], 4); // ...
      dat->byte--;
    }
  bit_write_BL (dat, dwg->header.dupls_refcount);   // dupl refcount
  bit_write_BL (dat, dwg->header.nums_dupls_handles);   // num dupl handles
  if (dwg->version >= R_2013)
    {
      BITCODE_BS tmp = 0;
      int i;
      for (i = 0; i < 8; i++)
        tmp |= ((BITCODE_BS)(dwg->header.unknown_1[i]) << (7 - i));
      bit_write_BS (dat, tmp); // unknown
    }
  else if (dwg->version >= R_2010)
    {
      BITCODE_BS tmp = 0;
      int i;
      for (i = 0; i < 8; i++)
        tmp |= ((BITCODE_BS)(dwg->header.unknown_1[i]) << (7 - i));
      bit_write_BS (dat, tmp); // unknown
    }
  else if (dwg->version >= R_2007)
    {
      BITCODE_BS tmp = 0;
      int i;
      for (i = 0; i < 8; i++)
        tmp |= ((BITCODE_BS)(dwg->header.unknown_1[i]) << (7 - i));
      bit_write_BS (dat, tmp); // unknown
    }
  else if (dwg->version >= R_2004)
    {
      BITCODE_BS tmp = 0;
      int i;
      for (i = 0; i < 8; i++)
        tmp |= ((BITCODE_BS)(dwg->header.unknown_1[i]) << (7 - i));
      bit_write_RC (dat, &tmp, 2); // unknown
    }
  else if (dwg->version >= R_2000)
    {
      BITCODE_BS tmp = 0;
      int i;
      for (i = 0; i < 8; i++)
        tmp |= ((BITCODE_BS)(dwg->header.unknown_1[i]) << (7 - i));
      bit_write_RC (dat, &tmp, 2); // unknown
    }

  dat->byte = start + size;
  if (!dwg)
    {
#if defined(LOGGING) && LOGGING > 0
      printf ("Header. No data.\n");
#endif
      return DWG_ERR_INVALIDDWG;
    }

  return 0;
}