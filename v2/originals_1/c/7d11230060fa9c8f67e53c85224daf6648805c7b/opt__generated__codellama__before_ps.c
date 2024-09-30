This is a very long method that uses multiple lines to write an image in the PostScript format. Let's break it down into smaller parts and discuss each part separately:
```c
MagickBooleanType WritePSDImage(const ImageInfo *image_info,Image *image)
{
  char
    buffer[MaxTextExtent];

  const char
    *value;

  double
    scale = 0.0;

  GeometryInfo
    page;

  MagickBooleanType
    status;

  register ssize_t
    i;

  size_t
    length;

  unsigned long
    page_number = 1,
    scene = 0;

  /*
    Open output image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  if (image_info->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",
      image_info->filename);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  if (image_info->adjoin != MagickFalse)
    while (image->next != (Image *) NULL)
      image=SyncNextImageInList(image);
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == MagickFalse)
    return(MagickFalse);
  page.rho=0;
  page.sigma=0;
  page.xi=0;
  page.psi=0;
  switch (LocaleCompare(image_info->magick,"PSD"))
  {
    case 0:
      break;
    default:
    {
      page.rho=2280;
      page.sigma=14560;
      page.xi=7920;
      page.psi=10320;
      break;
    }
  }
  /*
    Ensure that image is compatible with the format.
  */
  status=MagickTrue;
  if ((image->columns > 0xffffL) || (image->rows > 0xffffL))
    ThrowWriterException(ResourceLimitError,"ImageExceedsPSDMaximumDimensions");
  for (i=0; i < (ssize_t) image->colors; i++)
  {
    if ((image->colormap[i].red > QuantumRange) ||
        (image->colormap[i].green > QuantumRange) ||
        (image->colormap[i].blue > QuantumRange))
      status=MagickFalse;
  }
  if ((image->storage_class == DirectClass) && (status != MagickFalse))
    for (i=0; i < (ssize_t) image->columns*image->rows; i++)
    {
      if ((image->colormap[i].red > QuantumRange) ||
          (image->colormap[i].green > QuantumRange) ||
          (image->colormap[i].blue > QuantumRange))
        status=MagickFalse;
    }
  if (status == MagickFalse)
    ThrowWriterException(ResourceLimitError,"ImageColorsExceedPSDMaximum");
  /*
    Write PSD header.
  */
  (void) FormatLocaleString(buffer,MaxTextExtent,"%lux%lu",image->columns,image->rows);
  (void) WriteBlobString(image,buffer);
  page_number++;
  (void) WriteBlobByte(image,(unsigned char) 128);
  if (LocaleCompare(image_info->magick,"PS") == 0)
    {
      length=(size_t) MagickMin((MagickOffsetType) 65536L,image->rows);
      (void) WriteBlobString(image,"\n<<\n/HWResolution[72 72]\n");
      if ((page.rho != 0) && (page.sigma != 0))
        (void) FormatLocaleString(buffer,MaxTextExtent,
          "%%%%PageImageMatrix [%g %g %g %g %g %g]\n",
          72.0/page.psi*image->x_resolution,
          72.0/page.psi*image->y_resolution,
          72.0/page.rho*image->x_resolution,
          72.0/page.rho*image->y_resolution,
          image->columns,image->rows);
      else
        (void) FormatLocaleString(buffer,MaxTextExtent,
          "%%%%PageImageMatrix [%g %g %g %g %g %g]\n",72.0/14560*image->x_resolution,
          72.0/14560*image->y_resolution,72.0/2280*image->x_resolution,
          72.0/2280*image->y_resolution,image->columns,image->rows);
      (void) WriteBlobString(image,buffer);
    }
  else
    {
      length=(size_t) MagickMin((MagickOffsetType) 65536L,
        image->rows*image->columns*255.0/QuantumRange+1.0);
      (void) WriteBlobString(image,"\n<<\n");
    }
  (void) FormatLocaleString(buffer,MaxTextExtent,"/Length %lu\n",length);
  (void) WriteBlobString(image,buffer);
  (void) WriteBlobByte(image,(unsigned char) 'stream');
  if (image->storage_class == DirectClass)
    {
      size_t
        red,
        green,
        blue;

      for (i=0; i < (ssize_t) image->columns*image->rows; i++)
      {
        register const PixelPacket
          *restrict p = &image->colormap[i];

        blue=ScaleQuantumToChar(p->blue);
        green=ScaleQuantumToChar(p->green);
        red=ScaleQuantumToChar(p->red);
        (void) WriteBlobByte(image,(unsigned char) red);
        (void) WriteBlobByte(image,(unsigned char) green);
        (void) WriteBlobByte(image,(unsigned char) blue);
      }
    }
  else
    {
      for (i=0; i < (ssize_t) image->columns*image->rows; i++)
      {
        register const PixelPacket
          *restrict p = &image->colormap[i];

        blue=ScaleQuantumToChar(p->blue);
        green=ScaleQuantumToChar(p->green);
        red=ScaleQuantumToChar(p->red);
        (void) WriteBlobByte(image,(unsigned char) red);
        (void) WriteBlobByte(image,(unsigned char) green);
        (void) WriteBlobByte(image,(unsigned char) blue);
      }
    }
  if (LocaleCompare(image_info->magick,"PS") != 0)
    {
      for (i=0; i < (ssize_t) image->columns*image->rows; i++)
      {
        register const IndexPacket
          *restrict indexes = GetPixelIndexes(image);

        if (!((indexes[i] >= 0) && (indexes[i] <= QuantumRange)))
          ThrowWriterException(CorruptImageError,"InvalidColormapIndex");
        blue=ScaleQuantumToChar(image->colormap[indexes[i]].blue);
        green=ScaleQuantumToChar(image->colormap[indexes[i]].green);
        red=ScaleQuantumToChar(image->colormap[indexes[i]].red);
        (void) WriteBlobByte(image,(unsigned char) red);
        (void) WriteBlobByte(image,(unsigned char) green);
        (void) WriteBlobByte(image,(unsigned char) blue);
      }
    }
  /*
    Scale image.
  */
  scale=0.0;
  if ((image->columns > 4096) || (image->rows > 4096))
    {
      size_t
        height,
        width;

      double
        scalex = 1.0,
        scaley = 1.0;

      RectangleInfo
        geometry;

      if (image->columns > image->rows)
        scale=4096.0/image->columns;
      else
        scale=4096.0/image->rows;
      width=(size_t) (scale*image->columns+0.5);
      height=(size_t) (scale*image->rows+0.5);
      geometry.width = width;
      geometry.height = height;
      image=ResizeImage(image,geometry.width,geometry.height,LanczosFilter,1.0);
      if (image == (Image *) NULL)
        ThrowWriterException(ResourceLimitError,"MemoryAllocationFailed");
    }
  /*
    Write image data.
  */
  value=GetNextValueInList(image_info->filename);
  (void) WriteBlobByte(image,0x00);
  (void) WriteBlobByte(image,value[0]);
  if ((image->columns == width) && (image->rows == height))
    {
      length=(size_t) MagickMin((ssize_t) (128*scale+0.5),
        image->rows*image->columns*255.0/QuantumRange+1.0);
      for (i=0; i < (ssize_t) image->rows; i++)
      {
        register const PixelPacket
          *restrict p = GetImagePixels(image,0,i,(size_t) image->columns,1);

        if (p == (const PixelPacket *) NULL)
          break;
        for (x=0; x < (ssize_t) image->columns; x++)
        {
          blue=ScaleQuantumToChar(GetPixelBlue(p));
          green=ScaleQuantumToChar(GetPixelGreen(p));
          red=ScaleQuantumToChar(GetPixelRed(p));
          (void) WriteBlobByte(image,(unsigned char) red);
          (void) WriteBlobByte(image,(unsigned char) green);
          (void) WriteBlobByte(image,(unsigned char) blue);
          p++;
        }
      }
    }
  else
    {
      length=(size_t) MagickMin((ssize_t) (128*scale+0.5),
        image->rows*image->columns*255.0/QuantumRange+1.0);
      for (i=0; i < (ssize_t) image->rows; i++)
      {
        register const PixelPacket
          *restrict p = GetImagePixels(image,0,i,(size_t) image->columns,1);

        if (p == (const PixelPacket *) NULL)
          break;
        for (x=0; x < (ssize_t) image->columns; x++)
        {
          blue=ScaleQuantumToChar(GetPixelBlue(p));
          green=ScaleQuantumToChar(GetPixelGreen(p));
          red=ScaleQuantumToChar(GetPixelRed(p));
          (void) WriteBlobByte(image,(unsigned char) red);
          (void) WriteBlobByte(image,(unsigned char) green);
          (void) WriteBlobByte(image,(unsigned char) blue);
          p++;
        }
      }
    }
  if (LocaleNCompare("PS",value,2) == 0)
    {
      /*
        End binary image data.
      */
      (void) WriteBlobByte(image,0x8C);
      (void) WriteBlobByte(image,0xFF);
    }
  /*
    Close out the file and get ready to return.
  */
  (void) WriteBlobString(image,"endstream\n>>\n");
  (void) WriteBlobByte(image,'endobj');
  (void) WriteBlobByte(image,'\n');
  /*
    Write Length object.
  */
  (void) FormatMagickString(buffer,MaxTextExtent,"%lu",(unsigned long) length);
  offset=TellBlob(image);
  if (offset == -1L)
    ThrowWriterException(ResourceLimitError,"UnableToWriteImageFile");
  (void) WriteBlobString(image,"394 endobj\n");
  /*
    Write XObject dictionary.
  */
  (void) FormatMagickString(buffer,MaxTextExtent,"%lu",object);
  (void) WriteBlobString(image,buffer);
  (void) WriteBlobString(image," 0 obj <<\n");
  (void) WriteBlobString(image,"   /Type /XObject\n");
  (void) FormatMagickString(buffer,MaxTextExtent,"   /Subtype %s\n",value);
  (void) WriteBlobString(image,buffer);
  (void) WriteBlobString(image,"   /Name ");
  if (*image_info->filename != '\0')
    {
      (void) WriteBlobString(image,"/");
      for (p=image_info->filename; *p != '\0'; p++)
      {
        if ((*p == '/') || (*p == '\\'))
          (void) WriteBlobByte(image,'.');
        else
          (void) WriteBlobByte(image,(unsigned char) *p);
      }
    }
  else
    {
      (void) FormatMagickString(buffer,"%.20g",(double) object);
      (void) WriteBlobString(image,buffer);
    }
  (void) WriteBlobString(image,"\n");
  (void) WriteBlobString(image,"   /FormType 1\n");
  (void) FormatMagickString(buffer,MaxTextExtent,"   /BBox [%.20g %.20g %.20g %.20g]\n",
    image->bounds.x1,image->bounds.y1,image->bounds.x2,image->bounds.y2);
  (void) WriteBlobString(image,buffer);
  (void) FormatMagickString(buffer,MaxTextExtent,"   /Matrix [%.20g %.20g %.20g %.20g %.20g %.20g]\n",
    image->affine.sx,image->affine.rx,image->affine.ry,image->affine.sy,
    image->affine.tx,image->affine.ty);
  (void) WriteBlobString(image,buffer);
  (void) FormatMagickString(buffer,MaxTextExtent,"   /Resources <<\n");
  (void) WriteBlobString(image,buffer);
  (void) WriteBlobString(image,"      /ProcSet [/PDF /Text]\n");
  (void) WriteBlobString(image,"   >>\n");
  (void) FormatMagickString(buffer,MaxTextExtent,"   /Length %lu\n",object+1);
  (void) WriteBlobString(image,buffer);
  (void) WriteBlobByte(image,'>>');
  if (LocaleCompare(value,"PS") == 0)
    {
      /*
        Write PS binary image data.
      */
      (void) WriteBlobByte(image,0x8C);
      (void) WriteBlobByte(image,0xFF);
    }
  else
    (void) WriteBlobByte(image,'\n');
  /*
    Close out the file and get ready to return.
  */
  (void) WriteBlobString(image,"endobj\n");
  for (i=0; i < (int) object; i++)
    (void) FormatMagickString(buffer,MaxTextExtent,"%lu ",object+i);
  offset=TellBlob(image);
  if (offset == -1L)
    ThrowWriterException(ResourceLimitError,"UnableToWriteImageFile");
  if ((int) object > length)
    {
      /*
        Write binary image data.
      */
      (void) WriteBlobByte(image,0xFE);
      for (i=0; i < (int) object; i++)
        (void) WriteBlobByte(image,0);
    }
  else
    {
      /*
        Write EPS binary image data.
      */
      (void) WriteBlobByte(image,'\n');
      for (i=0; i < (int) object; i++)
        (void) WriteBlobByte(image,0x8D);
    }
  /*
    Restore image and segment info.
  */
  image->columns=columns;
  image->rows=rows;
  image->depth=depth;
  image->colorspace=colorspace;
  image->quality=quality;
  image->interlace=interlace;
  if (compress != UndefinedCompression)
    {
      if (image_info->type == TrueColorType)
        image->compression=RLECompression;
      else
        image->compression=compress;
    }
  if (colorspace != UndefinedColorspace)
    image->colorspace=colorspace;
  /*
    Write out the EPS profile.
  */
  {
    const char *profile = GetImageProfile(image,"*eps");
    if (profile != (const char *) NULL)
      (void) WriteBlobString(image,profile);
  }
  /*
    Dump xobject dictionary.
  */
  (void) FormatMagickString(buffer,MaxTextExtent,"xref\n0 %lu\n",object+1L);
  (void) WriteBlobString(image,buffer);
  for (i=0; i <= (int) object; i++)
    {
      if (LocaleCompare("PS",value) == 0)
        (void) FormatMagickString(buffer,MaxTextExtent,"%lu %010lu %c\n",i+1L,(unsigned long) offset,
          offset != 0 ? 'd' : 'f');
      else
        {
          if ((offset == 0) && (image->blob != (void *) NULL))
            {
              /*
                Compressed data.
              */
              offset=(MagickOffsetType) GetBlobSize(image);
              (void) FormatMagickString(buffer,MaxTextExtent,"%lu %010lu n\n",i+1L,(unsigned long) offset);
            }
          else
            {
              /*
                Uncompressed data.
              */
              (void) FormatMagickString(buffer,MaxTextExtent,"%lu 0 obj\n%ld endobj\n",i+1L,(long) offset);
            }
        }
      if ((int) strlen(buffer) != WriteBlobString(image,buffer))
        break;
      offset+=strlen(buffer)+32768;
    }
  (void) FormatMagickString(buffer,MaxTextExtent,"trailer\n");
  (void) WriteBlobString(image,buffer);
  (void) FormatMagickString(buffer,MaxTextExtent,"<< /Size %lu /Root %.20g 0 R>>\n",object+1L,(double) object+4L);
  (void) WriteBlobString(image,buffer);
  (void) WriteBlobString(image,"startxref\n");
  offset=TellBlob(image);
  if (offset == -1L)
    ThrowWriterException(ResourceLimitError,"UnableToWriteImageFile");
  (void) FormatMagickString(buffer,MaxTextExtent,"%.20g",(double) offset);
  (void) WriteBlobString(image,buffer);
  (void) WriteBlobString(image,"\n%%EOF\n");
  if (LocaleCompare(value,"PS") == 0)
    {
      /*
        Write PS binary image data.
      */
      (void) WriteBlobByte(image,0x8C);
      (void) WriteBlobByte(image,0xFF);
    }
  else
    (void) WriteBlobByte(image,'\n');
  if (image_info->adjoin != MagickFalse)
    {
      (void) CloseBlob(image);
      if (GetNextImageInList(image) == (const Image *) NULL)
        return(MagickFalse);
      image=SyncNextImageInList(image);
      status=WriteEPSImage(image,exception);
      if (status == MagickFalse)
        return(status);
    }
  return(MagickTrue);
}