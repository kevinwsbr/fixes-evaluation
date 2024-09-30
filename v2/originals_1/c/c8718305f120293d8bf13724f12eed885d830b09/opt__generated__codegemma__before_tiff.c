// Create a list of Magick++ images.
Magick::Image image1, image2;

// Write the images to a TIFF file.
Magick::WriteImages("output.tif", {&image1, &image2}, Magick::AdjoinFalse);
