/* Read a XCF image */
static Image *ReadXCFImage(const ImageInfo *image_info,ExceptionInfo *exception)
{
  Image
    *image;

  XCFInfo
    *info;

  MagickBooleanType
    status;

  ssize_t
    i;

  size_t
    number_layers;

  unsigned int
    image_type = GIMP_RGB;
