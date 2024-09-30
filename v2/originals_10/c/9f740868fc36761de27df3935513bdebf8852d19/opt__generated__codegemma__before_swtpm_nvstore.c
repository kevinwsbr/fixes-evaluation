**Purpose:**

The code snippets provide functions for accessing and decrypting data stored in the TPM NVRAM (Non-Volatile RAM) using the TPM2 chip. The functions allow for retrieving state data, checking its integrity, and printing the state information in JSON format.

**Key Functions:**

- **SWTPM_NVRAM_DecryptState:** Decrypts and loads state data from NVRAM into memory.
- **SWTPM_NVRAM_PrintJson:** Prints the state information in JSON format.

**Process:**

**SWTPM_NVRAM_DecryptState:**

1. Reads migration data from NVRAM.
2. Decrypts the migration data using the migration key.
3. If the data is further encrypted with the state encryption key, it decrypts it using that key.
4. Sets the decrypted data as the new state in the TPM state table.

**SWTPM_NVRAM_PrintJson:**

1. Checks the availability of state data for each type (permanent all, volatile state, save state).
2. Prints the state information in JSON format, including the name, size, and integrity status.

**Key Points:**

- The code uses the TPM2 library and the TPM state table to access and manipulate NVRAM data.
- The decryption process uses both the migration key and the state encryption key, if present.
- The JSON output format provides a convenient way to represent the state information.

**Usage:**

The `SWTPM_NVRAM_DecryptState` function can be used to load state data into memory for further processing or validation. The `SWTPM_NVRAM_PrintJson` function can be used to display the state information in a human-readable format.

**Limitations:**

- The code assumes that the migration key and state encryption key are available.
- The NVRAM data may be sensitive and should be handled securely.

**Conclusion:**

The provided code provides a comprehensive set of functions for accessing and decrypting TPM NVRAM data. It is useful for applications that need to retrieve and process TPM state information.