// Register an event handler for message type 1
ndp_register_msgrcv_handler(ndp, my_event_handler, 1, 0, NULL);

// Wait for events
while (true) {
    int fd = ndp_get_eventfd(ndp);
    fd_set rfds;
    FD_SET(fd, &rfds);
    select(fd + 1, &rfds, NULL, NULL, NULL);

    // Call the event handler
    ndp_call_eventfd_handler(ndp);
}
