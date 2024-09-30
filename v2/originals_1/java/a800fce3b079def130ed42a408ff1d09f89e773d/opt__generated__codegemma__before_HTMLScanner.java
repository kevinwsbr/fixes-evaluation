HTMLScanner scanner = new HTMLScanner();

// Read a single character from the buffer
int c = scanner.readPreservingBufferContent();

// Check if an end comment is available
boolean endCommentPresent = scanner.endCommentAvailable();

// Reduce the buffer to content between start and end markers
scanner.reduceToContent(buffer, "<start>", "</end>");
