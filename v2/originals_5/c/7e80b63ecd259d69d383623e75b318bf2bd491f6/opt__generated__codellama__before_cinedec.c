#include <libavformat/avformat.h>
#include <libavutil/mem.h>

typedef struct CineDemuxContext {
    int pts;
} CineDemuxContext;

static int cine_read_probe(AVProbeData *p) {
    if (p->buf[0] != 'P' || p->buf[1] != 'H' || p->buf[2] != 'N' || p->buf[3] != 'O') {
        return 0;
    }
    if (p->buf[4] != 'M' || p->buf[5] != 'P' || p->buf[6] != 'E' || p->buf[7] != 'G') {
        return 0;
    }
    return AVPROBE_SCORE_MAX / 2;
}

static int cine_read_header(AVFormatContext *avctx, AVFormatParameters *ap) {
    CineDemuxContext *cine = avctx->priv_data;
    AVStream *st = avformat_new_stream(avctx, NULL);
    AVIOContext *pb = avctx->pb;
    int64_t offImageOffsets;
    char description[DESCRIPTION_SIZE + 1];
    int i, ret;

    if (!st) {
        return AVERROR(ENOMEM);
    }

    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id = AV_CODEC_ID_RAWVIDEO;
    st->codecpar->format = AV_PIX_FMT_YUV420P;

    avio_skip(pb, 8); // PHNMMPEG
    offImageOffsets = avio_rl64(pb);
    avio_skip(pb, 48); // ImageWidth ... DescriptionSize
    st->codecpar->width = avio_rl32(pb);
    st->codecpar->height = avio_rl32(pb);

    avio_skip(pb, 120); // RisingEdge ... cmUser
    avio_rl64(pb); // ImageOffsetsCount
    avio_rl64(pb); // offImageOffsets
    avio_rl32(pb); // cbImageOffset

    avio_skip(pb, 24); // EDRShutterNs ... ImHeightAcq

#define DESCRIPTION_SIZE 4096
    description = av_malloc(DESCRIPTION_SIZE + 1);
    if (!description) {
        return AVERROR(ENOMEM);
    }
    i = avio_get_str(pb, DESCRIPTION_SIZE, description, DESCRIPTION_SIZE + 1);
    if (i < DESCRIPTION_SIZE) {
        avio_skip(pb, DESCRIPTION_SIZE - i);
    }
    if (description[0]) {
        av_dict_set(&st->metadata, "description", description, AV_DICT_DONT_STRDUP_VAL);
    } else {
        av_free(description);
    }

    avio_skip(pb, 1176); // RisingEdge ... cmUser

    set_metadata_int(&st->metadata, "enable_crop", avio_rl32(pb), 1);
    set_metadata_int(&st->metadata, "crop_left", avio_rl32(pb), 1);
    set_metadata_int(&st->metadata, "crop_top", avio_rl32(pb), 1);
    set_metadata_int(&st->metadata, "crop_right", avio_rl32(pb), 1);
    set_metadata_int(&st->metadata, "crop_bottom", avio_rl32(pb), 1);

    /* parse image offsets */
    while (avio_rl64(pb) > 0) {
        avio_skip(pb, 8); // Offset
        avio_skip(pb, 4); // cbImageOffset
    }

    ret = avformat_find_stream_info(avctx, NULL);
    if (ret < 0) {
        return ret;
    }

    return 0;
}

static int cine_read_packet(AVFormatContext *avctx, AVPacket *pkt) {
    CineDemuxContext *cine = avctx->priv_data;
    AVStream *st = avctx->streams[0];
    AVIOContext *pb = avctx->pb;
    int ret;

    /* read image data */
    ret = avio_read(pb, pkt->data, st->codecpar->width * st->codecpar->height * 3 / 2);
    if (ret < 0) {
        return ret;
    }

    pkt->size = ret;
    pkt->stream_index = 0;

    return ret;
}

AVInputFormat phnmpeg_demuxer = {
    .name           = "phnmpeg",
    .long_name      = NULL_IF_CONFIG_SMALL("PHNMMPEG format"),
    .priv_data_size = sizeof(CineDemuxContext),
    .read_probe     = cine_read_probe,
    .read_header    = cine_read_header,
    .read_packet    = cine_read_packet,
};
