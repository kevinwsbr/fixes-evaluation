// Register the DCM image format
size_t signature = RegisterDCMImage();

// Read a DCM image from a file
Image *image = ReadDCMImage("image.dcm");

// Check if the image was successfully read
if (image) {
  // Use the image data here
} else {
  // Handle the error
}

// Unregister the DCM image format
UnregisterDCMImage();
