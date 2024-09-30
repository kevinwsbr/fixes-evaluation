[PYTHON]
def save_data(filename, data):
    with open(filename, 'wb') as file:
        file.write(data)

def load_data(filename):
    with open(filename, 'rb') as file:
        return file.read()

def encrypt_blob(key, blob):
    cipher = AES.new(key, AES.MODE_CBC, IVEC_ENCRYPTED_DATA)
    return cipher.encrypt(blob)

def decrypt_blob(key, blob):
    cipher = AES.new(key, AES.MODE_CBC, IVEC_ENCRYPTED_DATA)
    return cipher.decrypt(blob)

def save_tpm_nvram_state(filename, state):
    key = os.urandom(16)
    blob = encrypt_blob(key, state)
    with open(filename, 'wb') as file:
        file.write(TAG_BLOB + TAG_ENCRYPTED_DATA + bytes([len(blob)]) + blob)

def load_tpm_nvram_state(filename):
    if not os.path.isfile(filename):
        return None
    with open(filename, 'rb') as file:
        tag = file.read(4)
        if tag != TAG_BLOB:
            return None
        tag = file.read(4)
        blob_len = int.from_bytes(file.read(2), byteorder='little')
        blob = file.read(blob_len)
        if tag == TAG_ENCRYPTED_DATA:
            key = os.urandom(16)
            return decrypt_blob(key, blob)
        elif tag == TAG_MIGRATION_DATA:
            key = os.urandom(16)
            return decrypt_blob(key, file.read())
        else:
            return blob

def main():
    save_data('nvram.bin', b'Hello world!')
    loaded = load_tpm_nvram_state('nvram.bin')
    print(loaded)

if __name__ == '__main__':
    main()
[/PYTHON]
[TESTS]
# Test case 1:
def test_save_and_load():
    with TemporaryDirectory() as temp_dir:
        filepath = os.path.join(temp_dir, "nvram.bin")
        data = b"Hello world!"
        save_data(filepath, data)
        loaded = load_tpm_nvram_state(filepath)
        assert loaded == data

# Test case 2:
def test_encrypted():
    with TemporaryDirectory() as temp_dir:
        filepath = os.path.join(temp_dir, "nvram.bin")
        key = os.urandom(16)
        data = encrypt_blob(key, b"Hello world!")
        save_data(filepath, data)
        loaded = load_tpm_nvram_state(filepath)
        assert loaded == data

# Test case 3:
def test_migrated():
    with TemporaryDirectory() as temp_dir:
        filepath = os.path.join(temp_dir, "nvram.bin")
        key = os.urandom(16)
        data = encrypt_blob(key, b"Hello world!")
        save_data(filepath, data)
        migrated = decrypt_blob(key, data)
        loaded = load_tpm_nvram_state(filepath)
        assert loaded == migrated
[/TESTS]
