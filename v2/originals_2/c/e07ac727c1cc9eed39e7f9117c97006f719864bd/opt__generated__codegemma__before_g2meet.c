// Create a decoder context
AVCodecContext *avctx = avcodec_alloc_context3(&ff_g2m_decoder);

// Set the decoder options
avctx->width = 640;
avctx->height = 480;

// Open the decoder
int ret = avcodec_open2(avctx, &ff_g2m_decoder, NULL);

// Use the decoder to decode video frames
// ...
