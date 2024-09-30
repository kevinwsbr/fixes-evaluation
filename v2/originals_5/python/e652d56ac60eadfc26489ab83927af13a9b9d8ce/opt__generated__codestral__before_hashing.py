import hashlib, base64, uuid
from cryptography.hazmat.primitives import hashes
from typing import Any

class Hashing():
    def __init__(self) -> None:
        self.salt = None

    def __call__(self, *args:Any):
        self.salt = args[0]

    def __str__(self) -> str:
        return "Hashing Functions In Here"

    def _hash_with_salt(self, data: bytes, salt: bytes = None) -> bytes:
        if not salt:
            salt = hashlib.sha256(uuid.uuid4().bytes).digest()
        return base64.urlsafe_b64encode(hashlib.pbkdf2_hmac('sha512', data, salt, 100000))

    def SHA256(self, data: str) -> bytes:
        hash = hashlib.sha256(data.encode()).digest()
        return self._hash_with_salt(hash, salt=self.salt)

    def SHA512(self, data: str) -> bytes:
        hash = hashlib.sha512(data.encode()).digest()
        return self._hash_with_salt(hash, salt=self.salt)

    def SHA384(self, data: str) -> bytes:
        hash = hashlib.sha384(data.encode()).digest()
        return self._hash_with_salt(hash, salt=self.salt)

    def BLAKE2(self, data: bytes) -> bytes:
        a = hashes.Hash(hashes.BLAKE2s(32))
        a.update(data)
        return self._hash_with_salt(a.finalize(), salt=self.salt)
