// Advise the kernel to keep pages from being swapped out.
int result = madvise(start_address, page_size, MADV_NO_SWAP);

// Check for errors.
if (result == 0) {
    // Success.
} else {
    // Error.
}
