// Calculate checksums for two data blocks
uLong crc1 = crc32(/* data block 1 */);
uLong crc2 = crc32(/* data block 2 */);

// Combine checksums
uLong combined_crc = crc32_combine(crc1, crc2, /* length of data block 2 */);
