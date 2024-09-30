[PYTHON]
import io

class ASFFile:
    def __init__(self, file):
        self.file = file
        self.offset = 0

    def read(self, size=-1):
        if size < 0:
            size = None
        return self.file.read(size)

    def seek(self, offset, whence=io.SEEK_SET):
        if whence == io.SEEK_END:
            offset = self.offset + offset
        elif whence == io.SEEK_CUR:
            offset = self.offset + offset
        self.file.seek(offset)
        self.offset = offset

    def tell(self):
        return self.offset
[/PYTHON]
