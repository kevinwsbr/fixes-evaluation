# Import the necessary TensorFlow operations
from tensorflow.image import decode_jpeg, decode_png, decode_gif, decode_bmp

# Decode an BMP image
bmp_image = decode_bmp(image_data)
