
This is an example implementation of the `handle_annotation` function that takes in a `struct magic_set` and a `struct magic`, and returns 1 if the mimetype or apple annotation was printed successfully, and -1 on error.

The function first checks if the flags for MAGIC_MIME_TYPE and MAGIC_APPLE are set. If they are not, it returns immediately with a value of 0.

Next, it checks whether the `firstline` argument is non-zero or not. If it is non-zero, the function assumes that this is the first match found in the file and does not print any newlines. If it is zero, the function prints a newline character followed by a dash '-' to separate the matches.

The function then checks whether the flags for MAGIC_MIME_TYPE and MAGIC_APPLE are set. If they are set, the function prints the mimetype or apple annotation in the file. The `file_printf` function is used to print the string "MIME-TYPE: ..." if the flag for MAGIC_MIME_TYPE is set, and "APPLE; ..." if the flag for MAGIC_APPLE is set. If either of these flags are not set, the function returns immediately with a value of 0.

The function returns 1 on success or -1 on error.