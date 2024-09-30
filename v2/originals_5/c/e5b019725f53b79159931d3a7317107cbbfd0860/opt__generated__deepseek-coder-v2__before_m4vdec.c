#include "avformat.h"
#include "rawdec.h"

#define VISUAL_OBJECT_START_CODE       0x000001b5
#define VOP_START_CODE                 0x000001b6

static int mpeg4video_probe(AVProbeData *probe_packet)
{
    uint32_t temp_buffer = -1;
    int VO = 0, VOL = 0, VOP = 0, VISO = 0, res = 0;
    int i;

    for (i = 0; i < probe_packet->buf_size; i++) {
        temp_buffer = (temp_buffer << 8) + probe_packet->buf[i];
        if ((temp_buffer & 0xffffff00) != 0x100)
            continue;

        if (temp_buffer == VOP_START_CODE)
            VOP++;
        else if (temp_buffer == VISUAL_OBJECT_START_CODE)
            VISO++;
        else if (temp_buffer < 0x120)
            VO++;
        else if (temp_buffer < 0x130)
            VOL++;
        else if (!(0x1AF < temp_buffer && temp_buffer < 0x1B7) &&
                 !(0x1B9 < temp_buffer && temp_buffer < 0x1C4))
            res++;
    }

    // Ensure that the pointers are not dereferenced if they are NULL to avoid null pointer dereference vulnerability.
    if (VOP >= VISO && VOP >= VOL && VO >= VOL && VOL > 0 && res == 0)
        return AVPROBE_SCORE_EXTENSION;
    return 0;
}

FF_DEF_RAWVIDEO_DEMUXER(m4v, "raw MPEG-4 video", mpeg4video_probe, "m4v",
                        AV_CODEC_ID_MPEG4)
