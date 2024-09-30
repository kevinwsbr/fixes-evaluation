**Purpose:**

The code snippet you provided is a C function called `gf_m2ts_restamp()` that performs M2TS resampling. It processes a buffer of data containing M2TS packets and adjusts the presentation timestamps (PTS) and decoder timestamps (DTS) of the packets.

**Input:**

* `buffer`: A pointer to an array of bytes containing M2TS packets.
* `size`: The size of the buffer in bytes.

**Output:**

* `GF_OK`: If the resampling was successful.
* `GF_NON_COMPLIANT_BITSTREAM`: If an invalid sync byte is encountered.
* `GF_IO_ERR`: If a sanity check fails.

**Algorithm:**

* The function iterates through the buffer, processing each M2TS packet.
* It extracts the packet header, adaptation field, and payload.
* For PES packets, it checks for the start code and adjusts the PTS and DTS if they are present.
* The function uses the `gf_m2ts_get_pts()` function to extract the PTS and DTS from the PES header.
* The `ADJUST_TIMESTAMP()` macro adjusts the PTS and DTS values to account for the difference between the original and resampled timestamps.
* The function returns `GF_OK` if all packets are successfully resampled, or an error code if an issue is encountered.

**Key Points:**

* M2TS resampling adjusts timestamps to ensure that the presentation and decoding order of packets is preserved.
* The `gf_m2ts_get_pts()` function is used to extract timestamps from PES headers.
* The `ADJUST_TIMESTAMP()` macro is used to adjust timestamps based on the difference between the original and resampled timestamps.
* Error handling is included to handle invalid sync bytes and sanity check failures.

**Usage:**

The `gf_m2ts_restamp()` function can be used to resample M2TS streams in a streaming or file-based environment. It is typically used in conjunction with other M2TS decoding and processing functions.