
[PYTHON]
import struct

def gf_odf_ac3_cfg_parse(dsi: bytes, is_ec3: bool) -> dict:
    cfg = {}
    bs = gf_bs_new(dsi, len(dsi), GF_BITSTREAM_READ)
    e = gf_odf_ac3_config_parse_bs(bs, is_ec3, cfg)
    if is_ec3 and gf_bs_available(bs) >= 2:
        cfg['atmos_ec3_ext'] = gf_bs_read_int(bs, 1)
        cfg['complexity_index_type'] = gf_bs_read_u8(bs)
    gf_bs_del(bs)
    return e

def gf_odf_opus_cfg_parse(dsi: bytes) -> dict:
    cfg = {}
    bs = gf_bs_new(dsi, len(dsi), GF_BITSTREAM_READ)
    e = gf_odf_opus_cfg_parse_bs(bs, cfg)
    gf_bs_del(bs)
    return e

def gf_odf_ac3_cfg_write(cfg: dict, is_ec3: bool) -> bytes:
    bs = gf_bs_new(None, 0, GF_BITSTREAM_WRITE)
    e = gf_odf_ac3_cfg_write_bs(bs, cfg, is_ec3)
    data = None
    size = 0
    if bs:
        data = gf_bs_get_content(bs)
        size = len(data)
    gf_bs_del(bs)
    return e, data, size

def gf_odf_opus_cfg_write(cfg: dict) -> bytes:
    bs = gf_bs_new(None, 0, GF_BITSTREAM_WRITE)
    e = gf_odf_opus_cfg_write_bs(bs, cfg)
    data = None
    size = 0
    if bs:
        data = gf_bs_get_content(bs)
        size = len(data)
    gf_bs_del(bs)
    return e, data, size
[/PYTHON]
