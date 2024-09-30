js_string compressed_data = ...;
js_string uncompressed_data = ...;

int status = decompress_data(&compressed_data, &uncompressed_data);

if (status == JS_SUCCESS) {
    // Decompression successful
} else {
    // Error during decompression
}
