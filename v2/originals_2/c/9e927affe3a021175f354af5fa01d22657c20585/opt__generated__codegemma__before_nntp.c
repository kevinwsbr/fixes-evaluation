// Check children of message with ID "message-id"
int status = nntp_check_children(ctx, "message-id");

// Check if the operation was successful
if (status == 0) {
    // Child articles retrieved successfully
} else {
    // Error retrieving child articles
}
