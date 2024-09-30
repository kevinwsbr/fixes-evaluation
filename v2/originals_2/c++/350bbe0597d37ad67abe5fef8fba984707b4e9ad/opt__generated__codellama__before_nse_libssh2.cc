[PYTHON]
import lua

def main():
    libssh2 = lua.eval("require 'libssh2'")
    session = libssh2.session_open()
    hostkey_hash = libssh2.hostkey_hash(session)
    print(hostkey_hash)
    session.close()

if __name__ == "__main__":
    main()
[/PYTHON]
[TESTS]
# Test case 1:
def test_libssh2():
    libssh2 = lua.eval("require 'libssh2'")
    session = libssh2.session_open()
    hostkey_hash = libssh2.hostkey_hash(session)
    assert len(hostkey_hash) > 0
    session.close()

test_libssh2()
[/TESTS]
