void usage(void) {
    (void) fprintf(stderr,
        "usage: scp [-1246BCpqrv] [-c cipher] [-F ssh_config] [-i identity_file]\n"
        "           [-l limit] [-P port] [-S program]\n"
        "           [[user@]host1:]file1 [...] [[user@]host2:]file2\n");
    exit(1);
}
