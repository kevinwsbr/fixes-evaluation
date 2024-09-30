regex_t re_media = REGEX_COMP("video");
regex_t re_transport = REGEX_COMP("UDP");

int stream_found = stream_find(sip_msg, &re_media, &re_transport);
