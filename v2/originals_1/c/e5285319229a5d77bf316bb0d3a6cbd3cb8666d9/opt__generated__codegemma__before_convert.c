// Load an image using opj_image_read()
opj_image_t *image = ...;

// Convert to raw file with lossless scaling
int result = imagetoraw(image, "output.raw");

// Convert to raw file without lossless scaling
int result = imagetorawl(image, "output_lossless.raw");
