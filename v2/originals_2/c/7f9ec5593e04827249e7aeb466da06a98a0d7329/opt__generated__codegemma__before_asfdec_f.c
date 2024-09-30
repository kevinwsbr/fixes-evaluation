// Create an ASF demuxer instance
AVFormatContext *fmt_ctx = avformat_alloc_context3(&ff_asf_demuxer, NULL, NULL);

// Open the ASF file
if (avformat_open_input(&fmt_ctx, "input.asf", NULL, NULL) < 0) {
    // Error opening file
}

// Read and decode ASF packets
while (av_read_frame(fmt_ctx, &packet) >= 0) {
    // Process the packet data
}

// Close the ASF file
avformat_close_input(&fmt_ctx);
