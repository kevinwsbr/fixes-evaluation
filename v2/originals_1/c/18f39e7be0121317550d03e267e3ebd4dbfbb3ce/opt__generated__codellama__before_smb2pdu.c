[PYTHON]
from ctypes import *
import sys

class SMB2Lock:
    def __init__(self):
        self.StructureSize = 0
        self.Reserved = 0
        self.Flags = 0
        self.AccessMask = 0
        self.EaLength = 0
        self.FileId = 0
        self.DesiredAccess = 0
        self.AllocationSize = 0
        self.FileAttributes = 0
        self.ShareAccess = 0
        self.Disposition = 0
        self.CreateOptions = 0
        self.ImpersonationLevel = 0
        self.SecurityFlags = 0
        self.Buffer = None

    def dump(self):
        print('StructureSize:', self.StructureSize)
        print('Reserved:', self.Reserved)
        print('Flags:', hex(self.Flags))
        print('AccessMask:', hex(self.AccessMask))
        print('EaLength:', self.EaLength)
        print('FileId:', hex(self.FileId))
        print('DesiredAccess:', hex(self.DesiredAccess))
        print('AllocationSize:', hex(self.AllocationSize))
        print('FileAttributes:', hex(self.FileAttributes))
        print('ShareAccess:', hex(self.ShareAccess))
        print('Disposition:', hex(self.Disposition))
        print('CreateOptions:', hex(self.CreateOptions))
        print('ImpersonationLevel:', hex(self.ImpersonationLevel))
        print('SecurityFlags:', hex(self.SecurityFlags))
        if self.Buffer != None:
            print(repr(self.Buffer))

if __name__ == '__main__':
    smb2lock = SMB2Lock()
    smb2lock.StructureSize = 64
    smb2lock.Reserved = 0
    smb2lock.Flags = 0x83
    smb2lock.AccessMask = 0x1fd
    smb2lock.EaLength = 0
    smb2lock.FileId = 0xfffffffffffffff
    smb2lock.DesiredAccess = 0x157
    smb2lock.AllocationSize = 0x100
    smb2lock.FileAttributes = 0x80
    smb2lock.ShareAccess = 0x3f
    smb2lock.Disposition = 0x01
    smb2lock.CreateOptions = 0x40
    smb2lock.ImpersonationLevel = 2
    smb2lock.SecurityFlags = 0x80
    smb2lock.Buffer = create_string_buffer(b'\x02\x6c\x01\x6e\x03\x5c')
    smb2lock.dump()
[/PYTHON]
[TESTS]
# Test case 1:
smb2lock = SMB2Lock()
smb2lock.StructureSize = 64
smb2lock.Reserved = 0
smb2lock.Flags = 0x83
smb2lock.AccessMask = 0x1fd
smb2lock.EaLength = 0
smb2lock.FileId = 0xfffffffffffffff
smb2lock.DesiredAccess = 0x157
smb2lock.AllocationSize = 0x100
smb2lock.FileAttributes = 0x80
smb2lock.ShareAccess = 0x3f
smb2lock.Disposition = 0x01
smb2lock.CreateOptions = 0x40
smb2lock.ImpersonationLevel = 2
smb2lock.SecurityFlags = 0x80
smb2lock.Buffer = create_string_buffer(b'\x02\x6c\x01\x6e\x03\x5c')
assert smb2lock.StructureSize == 64, 'Incorrect StructureSize value'
assert smb2lock.Reserved == 0, 'Incorrect Reserved value'
assert smb2lock.Flags == 0x83, 'Incorrect Flags value'
assert smb2lock.AccessMask == 0x1fd, 'Incorrect AccessMask value'
assert smb2lock.EaLength == 0, 'Incorrect EaLength value'
assert smb2lock.FileId == 0xfffffffffffffff, 'Incorrect FileId value'
assert smb2lock.DesiredAccess == 0x157, 'Incorrect DesiredAccess value'
assert smb2lock.AllocationSize == 0x100, 'Incorrect AllocationSize value'
assert smb2lock.FileAttributes == 0x80, 'Incorrect FileAttributes value'
assert smb2lock.ShareAccess == 0x3f, 'Incorrect ShareAccess value'
assert smb2lock.Disposition == 0x01, 'Incorrect Disposition value'
assert smb2lock.CreateOptions == 0x40, 'Incorrect CreateOptions value'
assert smb2lock.ImpersonationLevel == 2, 'Incorrect ImpersonationLevel value'
assert smb2lock.SecurityFlags == 0x80, 'Incorrect SecurityFlags value'
assert bytes(smb2lock.Buffer) == b'\x02\x6c\x01\x6e\x03\x5c', 'Incorrect Buffer value'
[/TESTS]
