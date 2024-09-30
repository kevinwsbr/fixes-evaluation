
[PYTHON]
import errno

class NBDError(Exception):
    def __init__(self, error_code, message=None):
        self.error_code = error_code
        if message is None:
            message = f"Unknown error {error_code}"
        super().__init__(message)

class NBDRequest:
    def __init__(self, from_, len_, handle, flags, type_):
        self.from_ = from_
        self.len = len_
        self.handle = handle
        self.flags = flags
        self.type = type_

class NBDReply:
    def __init__(self, error, handle):
        self.error = error
        self.handle = handle

def nbd_errno_to_system_errno(errno):
    if errno == 0:
        return None
    else:
        return NBDError(errno)

# mock implementation of the libnbd library for python
def nbd_init(fd, ioc, flags, size):
    if flags != 0 or size != 0:
        raise ValueError("unsupported flags and size")
    return 0

def nbd_client(fd):
    return 0

def nbd_disconnect(fd):
    return 0

def nbd_send_request(ioc, request):
    # send the request to the server
    buf = bytearray([0x4e, 0x42, 0x44, 0x53, 0x08, request.flags, request.type,
                     int(request.handle), int(request.from_), int(request.len)])
    ioc.write_sync(buf, len(buf))
    return 0

def nbd_receive_reply(ioc, reply):
    # receive the reply from the server
    buf = bytearray(8)
    bytes_read = ioc.read_sync(buf, len(buf))
    if bytes_read < 0:
        return bytes_read
    elif bytes_read != len(buf):
        raise ValueError("invalid reply size")

    # parse the reply
    error = buf[4]
    handle = struct.unpack(">Q", buf[8:])[0]
    reply.error = nbd_errno_to_system_errno(error)
    reply.handle = handle
    return 0
[/PYTHON]
