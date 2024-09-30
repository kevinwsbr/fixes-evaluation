 /*
     * Read RLE encoded pixels.
     */
    number_packets=258;
    x=0;
    y=0;
    while (!EOFBlob(image))
    {
      count=ReadBlobByte(image);
      if (count < 0)
        break;
      if (count > 127)
        {
          /*
            Copy next count pixels from the file to the image.
          */
          count-=128;
          number_packets-=(count+1);
          count++;
          if ((x+count) > columns)
            {
              count=(unsigned long) (columns-x)+1;
              number_packets+=((int) (x+count)-(int) columns);
            }
          while (count-- != 0)
          {
            c=ReadBlobByte(image);
            if (c < 0)
              break;
            PaintPixel(pixel_info,c,1);
            x++;
            if (x == columns)
              {
                y++;
                if (y >= rows)
                  break;
                number_packets-=(columns-(int) x);
                x=0;
              }
          }
        }
      else
        {
          /*
            Replicate next pixel count times.
          */
          if ((x+count) > columns)
            count=(unsigned long) (columns-x)+1;
          number_packets-=(count+1);
          c=ReadBlobByte(image);
          if (c < 0)
            break;
          PaintPixel(pixel_info,c,count);
          x+=count;
          while ((x >= columns) && (y < rows))
          {
            number_packets-=(columns-(int) x);
            y++;
            x=0;
          }
        }
      if (((image->progress_monitor != (MagickProgressMonitor) NULL) &&
           (QuantumTick(y,rows) != MagickFalse)) ||
          (y >= rows))
        {
          status=SetImageProgress(image,LoadImageTag,(MagickOffsetType) y,
            rows);
          if (status == MagickFalse)
            break;
        }
    }

  /*
     * Transfer pixels from pixel_info to the image.
   */