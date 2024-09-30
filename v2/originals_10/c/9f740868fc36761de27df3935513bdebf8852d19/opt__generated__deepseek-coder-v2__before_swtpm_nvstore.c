if (is_encrypted || (hdrflags & BLOB_FLAG_ENCRYPTED)) {
    if (!SWTPM_NVRAM_Has_FileKey()) {
        logprintf(STDERR_FILENO, "Missing state key to decrypt %s\n", blobname);
        res = TPM_KEYNOTFOUND;
        goto cleanup;
    }

    res = SWTPM_NVRAM_DecryptData(&filekey, &plain, &plain_len,
                                  mig_decrypt, mig_decrypt_len,
                                  TAG_ENCRYPTED_DATA,
                                  hdrversion, TAG_IVEC_ENCRYPTED_DATA,
                                  hdrflags, BLOB_FLAG_ENCRYPTED_256BIT_KEY);
    if (res) {
        logprintf(STDERR_FILENO, "Decrypting the %s blob with the state key failed; res = %d\n", blobname, res);
        goto cleanup;
    }
} else {
    res = SWTPM_NVRAM_GetPlainData(&plain, &plain_len,
                                   mig_decrypt, mig_decrypt_len,
                                   TAG_DATA, hdrversion);
    if (res)
        goto cleanup;
}
