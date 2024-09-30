// Create a 1024-byte byte array.
ByteArray array(1024);

// Write some data to the array.
array.Put(0, (uint8_t*)"Hello", 0, 6);

// Copy the data to an OutputStream.
OutputStream os;
array.CopyTo(&os);
