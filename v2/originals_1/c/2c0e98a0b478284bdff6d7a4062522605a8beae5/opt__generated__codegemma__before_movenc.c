// Create an output file in the 3GP format
AVFormatContext *oc = avformat_alloc_context();
oc->oformat = &ff_3gp_muxer;
