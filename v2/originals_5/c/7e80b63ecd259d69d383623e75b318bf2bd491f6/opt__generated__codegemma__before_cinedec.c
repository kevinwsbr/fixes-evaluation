AVFormatContext *avformat_alloc_context3(void);

// Open the Cine file
AVFormatContext *avformat = avformat_alloc_context3();
if (avformat_open_input(&avformat, "path/to/cine.cine", NULL, NULL) != 0) {
    // Handle error
}
