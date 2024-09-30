[PYTHON]
import errno
from typing import Optional

def safe_close(fd: Optional[int]) -> int:
    if fd is None or fd < 0:
        return -1
    try:
        return close(fd)
    except OSError as e:
        if e.errno == errno.EBADF:
            # ignore errors where the fd is already closed
            return -1
        raise
[PYTHON]
