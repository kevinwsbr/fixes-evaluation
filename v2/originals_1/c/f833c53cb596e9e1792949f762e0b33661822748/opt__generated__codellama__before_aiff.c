[PYTHON]
def get_sample_rate(file):
    return file.read(4)

def get_channel_count(file):
    return file.read(2)

def get_interleaved(file):
    return file.read(1)[0] == 1

def get_sample_format(file):
    format = file.read(2)
    if format == b'\x00\x08':
        return 'u8'
    elif format == b'\x00\x09':
        return 's8'
    elif format == b'\x00\x10':
        return 'u16'
    elif format == b'\x00\x11':
        return 's16'
    elif format == b'\x00\x20':
        return 'u24'
    elif format == b'\x00\x21':
        return 's24'
    elif format == b'\x00\x30':
        return 'u32'
    elif format == b'\x00\x31':
        return 's32'
    else:
        raise ValueError('unknown sample format')

def get_samples(file, count):
    samples = []
    for _ in range(count):
        samples.append((ord(file.read(1)[0]) / 65536.0,))
    return tuple(samples)
[/PYTHON]
