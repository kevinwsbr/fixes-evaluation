 /*
     * Reads a 32-bit big endian integer from the file. Returns the number of
     * bytes read, or EOF on error
     */
    static size_t xcf_read_int32 (FILE *file, int32_t *valp, ssize_t n) {
        uint8_t buf[4];
        size_t i;

        for (i = 0; i < n; i++) {
            if (fread (buf, 1, 4, file) != 4) {
                return EOF;
            }

            valp[i] = ((int32_t) buf[0]) << 24 | ((int32_t) buf[1]) << 16 |
                ((int32_t) buf[2]) << 8 | (int32_t) buf[3];
        }

        return n * 4;
    }

    /*
     * Seeks to the specified position in the file. Returns 0 on success, or
     * EOF on error
     */
    static size_t xcf_seek_pos (XCFInfo *info, long offset) {
        if (offset < 0 || offset > info->file_size) {
            return EOF;
        } else {
            fseek (info->fp, offset, SEEK_SET);
            return 0;
        }
    }

    /*
     * Loads an image from the current position in the file. Returns a pointer
     * to the new image on success or NULL on error
     */
    static GimpImage *xcf_load_image (XCFInfo *info) {
        GimpImage       *gimage;
        gint             width, height;
        gint             i, j, num_successful_elements = 0;
        int32_t          offset;
        long            saved_pos;
        GimpLayer       *layer;
        GimpChannel     *channel;

        /* read in the width and height */
        info->cp += xcf_read_int32 (info->fp, &width, 1);
        info->cp += xcf_read_int32 (info->fp, &height, 1);

        gimage = gimp_create_image (width, height, GIMP_RGB, TRUE);

        while (TRUE) {
            /* read in the offset of the next layer */
            info->cp += xcf_read_int32 (info->fp, &offset, 1);

            /* if the offset is 0 then we are at the end
             * of the layer list.
             */
            if (offset == 0)
                break;

            /* save the current position as it is where the
             * next layer offset is stored.
             */
            saved_pos = info->cp;

            /* seek to the layer offset */
            xcf_seek_pos (info, offset);

            /* read in the layer */
            layer = xcf_load_layer (info, gimage);
            if (layer == NULL)
                goto error;

            num_successful_elements++;

            /* add it to the image. */
            gimp_image_add_layer (gimage, layer, -1, TRUE);

            /* restore the saved position so we'll be ready to
             * read the next offset.
             */
            xcf_seek_pos (info, saved_pos);
        }

        while (TRUE) {
            /* read in the offset of the next channel */
            info->cp += xcf_read_int32 (info->fp, &offset, 1);

            /* if the offset is 0 then we are at the end
             * of the channel list.
             */
            if (offset == 0)
                break;

            /* save the current position as it is where the
             * next channel offset is stored.
             */
            saved_pos = info->cp;

            /* seek to the channel offset */
            xcf_seek_pos (info, offset);

            /* read in the layer */
            channel = xcf_load_channel (info, gimage);
            if (channel == NULL)
                goto error;

            num_successful_elements++;

            /* add the channel to the image. */
            gimp_image_add_channel (gimage, channel, -1);

            /* restore the saved position so we'll be ready to
             * read the next offset.
             */
            xcf_seek_pos (info, saved_pos);
        }

        if (num_successful_elements == 0) {
            gimp_image_undo_disable (gimage);
            goto error;
        }

        /* we should have exactly one layer and channel */
        g_assert (gimp_image_get_layer_iter (gimage)->data != NULL);
        g_assert (gimp_image_get_channel_iter (gimage)->data == NULL ||
                  g_list_length (gimp_image_get_channel_iter (gimage)->data) == 1);

        return gimage;

    error:
        if (gimage != NULL)
            gimp_image_delete (gimage);
        return NULL;
    }

    /*
     * Loads a layer from the current position in the file. Returns a pointer to
     * the new layer on success or NULL on error
     */
    static GimpLayer *xcf_load_layer (XCFInfo *info, GimpImage *gimage) {
        int32_t          width, height;
        int32_t          type, visible, linked, locked, floating_sel, opacity, mode;
        int32_t          offset, mask_offset, length, top, left, right, bottom;
        GimpLayer       *layer;
        GimpChannel     *mask = NULL;
        GimpDrawable    *drawable;
        gchar           *name;
        gint             num_props;
        gpointer         image_data;
        gsize            image_length;
        guint8          *image_pixels = NULL;
        gboolean         has_selection;
        GimpParasite    *parasite;

        info->cp += xcf_read_int32 (info->fp, &width, 1);
        info->cp += xcf_read_int32 (info->fp, &height, 1);
        info->cp += xcf_read_int32 (info->fp, &type, 1);
        info->cp += xcf_read_int32 (info->fp, &visible, 1);
        info->cp += xcf_read_int32 (info->fp, &linked, 1);
        info->cp += xcf_read_int32 (info->fp, &locked, 1);
        info->cp += xcf_read_int32 (info->fp, &floating_sel, 1);
        info->cp += xcf_read_int32 (info->fp, &opacity, 1);
        info->cp += xcf_read_int32 (info->fp, &mode, 1);
        info->cp += xcf_read_int32 (info->fp, &offset, 1);
        info->cp += xcf_read_int32 (info->fp, &mask_offset, 1);
        info->cp += xcf_read_int32 (info->fp, &length, 1);

        /* the name is a pascal string */
        name = gimp_any_to_utf8 ((const guint8 *) &(info->cp), -1, NULL);
        info->cp += strlen (name) + 1;

        if (width != gimage->width || height != gimage->height) {
            fprintf(stderr, "Warning: Image and layer dimensions don't match!\n");
            width = MIN(width, gimage->width);
            height = MIN(height, gimage->height);
        }

        /* create the new layer */
        layer = gimp_layer_new (width, height, GIMP_RGB_IMAGE, name, opacity / 255.0, TRUE);
        g_free (name);
        drawable = GIMP_DRAWABLE (layer);

        if (!visible) {
            gimp_item_set_visible (GIMP_ITEM (drawable), FALSE);
        }

        if (linked) {
            gimp_item_set_linked (GIMP_ITEM (drawable), TRUE);
        }

        if (locked) {
            gimp_item_set_lock_content (GIMP_ITEM (drawable), TRUE);
        }

        if (floating_sel) {
            gimp_image_set_floating_sel (gimage, layer);
        }

        /* read the tile data */
        image_data = gimp_xcf_read_tile_data (info->fp, width, height, type, length, &image_length, &has_selection, &top, &left, &right, &bottom);

        if (!image_data || image_length == 0) {
            fprintf(stderr, "Error: Could not read layer tile data!\n");
            gimp_item_delete (GIMP_ITEM (drawable));
            return NULL;
        }

        /* load the selection */
        if (has_selection) {
            GimpChannel *sel = gimp_channel_new (width, height, "Selection", FALSE);
            guint8 *mask = gimp_drawable_get_mask (GIMP_DRAWABLE (layer));

            if (!mask) {
                fprintf(stderr, "Error: Could not allocate memory for layer mask!\n");
                gimp_item_delete (GIMP_ITEM (sel));
                gimp_item_delete (GIMP_ITEM (drawable));
                return NULL;
            }

            memcpy(mask, image_data + image_length - width * height, width * height);
            gimp_drawable_update (GIMP_DRAWABLE (layer), left, top, right - left, bottom - top);
        }

        /* load the layer mask */
        if (mask_offset) {
            long saved_pos = ftell(info->fp);

            fseek(info->fp, info->sp + mask_offset, SEEK_SET);
            mask = xcf_load_channel(info, gimage);

            if (!mask) {
                fprintf(stderr, "Warning: Could not load layer mask!\n");
            }

            fseek(info->fp, saved_pos, SEEK_SET);
        }

        /* check for a layer masks parasite */
        parasite = gimp_parasite_find (layer->parasites, "gimp-layer-mask-offsets");

        if (parasite) {
            GValueArray *array;

            array = (GValueArray *) gimp_parasite_data (parasite);

            if (array && array->n_values == 4) {
                top    = g_value_get_int (&g_value_array_index (array, 0));
                left   = g_value_get_int (&g_value_array_index (array, 1));
                bottom = g_value_get_int (&g_value_array_index (array, 2));
                right  = g_value_get_int (&g_value_array_index (array, 3));
            }
        }

        /* set the layer mask */
        if (mask) {
            gimp_layer_add_mask (layer, mask, FALSE);
            gimp_rectangle_set_values (&layer->mask_bounds, left, top, right - left, bottom - top);
        } else {
            /* create an empty layer mask */
            GimpChannel *channel = gimp_channel_new (gimage->width, gimage->height, "Mask", FALSE);
            gimp_layer_add_mask (layer, channel, FALSE);
            gimp_drawable_fill (GIMP_DRAWABLE(channel), 0.0);
        }

        /* set the layer mode */
        if (mode >= 0 && mode < GIMP_LAYER_MODE_EFFECTS) {
            gimp_layer_set_mode (layer, mode);
        } else {
            fprintf(stderr, "Warning: Unknown layer mode!\n");
        }

        /* read the layer properties */
        num_props = xcf_read_properties(info->fp, &layer->parasites);

        /* convert the tile data to pixels */
        image_pixels = gimp_xcf_tile_data_to_pixels (image_data, width, height, type, has_selection);
        g_free (image_data);

        if (!image_pixels) {
            fprintf(stderr, "Error: Could not convert layer tile data to pixels!\n");
            gimp_item_delete (GIMP_ITEM (drawable));
            return NULL;
        }

        /* set the layer contents */
        gimp_pixel_rgn_init (&layer->content_invalid, drawable, 0, 0, width, height, FALSE, FALSE);
        gimp_drawable_push_undo (GIMP_DRAWABLE (layer));
        gimp_pixel_rgn_set_rect (&layer->content_invalid, image_pixels, 0, 0, TRUE);

        return layer;
    }

    GimpChannel *xcf_load_channel(XcfInfo *info, GimpImage *image) {
        guint32 width, height;
        gchar name[256];
        guint32 type, length;
        gsize image_length;
        gpointer image_data;
        guint8 *pixels;
        gboolean has_selection;
        GimpChannel *channel;
        GimpRGB color;
        int top, left, right, bottom;

        if (fread(&width, 4, 1, info->fp) != 1 || fread(&height, 4, 1, info->fp) != 1) {
            fprintf(stderr, "Error: Could not read channel width and height!\n");
            return NULL;
        }

        if (fgets(name, 256, info->fp) == NULL || name[strlen(name)-1] != '\n') {
            fprintf(stderr, "Error: Could not read channel name!\n");
            return NULL;
        }

        /* remove trailing newline */
        name[strlen(name)-1] = '\0';

        if (fread(&type, 4, 1, info->fp) != 1 || fread(&length, 4, 1, info->fp) != 1) {
            fprintf(stderr, "Error: Could not read channel type and length!\n");
            return NULL;
        }

        image_data = gimp_xcf_read_tile_data (info->fp, width, height, type, length, &image_length, &has_selection, &top, &left, &right, &bottom);

        if (!image_data || image_length == 0) {
            fprintf(stderr, "Error: Could not read channel tile data!\n");
            return NULL;
        }

        pixels = gimp_xcf_tile_data_to_pixels (image_data, width, height, type, has_selection);
        g_free (image_data);

        if (!pixels) {
            fprintf(stderr, "Error: Could not convert channel tile data to pixels!\n");
            return NULL;
        }

        channel = gimp_channel_new (width, height, name, FALSE);

        /* set the channel contents */
        gimp_pixel_rgn_init (&channel->bounds, GIMP_DRAWABLE (channel), 0, 0, width, height, FALSE, FALSE);
        gimp_drawable_push_undo (GIMP_DRAWABLE (channel));
        gimp_pixel_rgn_set_rect (&channel->bounds, pixels, 0, 0, TRUE);

        /* set the channel color */
        if (gimp_palette_lookup ("Web", name, &color)) {
            gimp_drawable_set_color (GIMP_DRAWABLE (channel), &color);
        }

        return channel;
    }