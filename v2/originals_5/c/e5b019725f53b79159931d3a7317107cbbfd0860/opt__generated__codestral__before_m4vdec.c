    static int mpeg4video_probe(AVProbeData *probe_packet) {
        uint32_t temp_buffer = -1;
        ....
        for (i = 0; i < probe_packet->buf_size; i++) {
            temp_buffer = (temp_buffer << 8) + probe_packet->buf[i];
            ....
        }
    }
    