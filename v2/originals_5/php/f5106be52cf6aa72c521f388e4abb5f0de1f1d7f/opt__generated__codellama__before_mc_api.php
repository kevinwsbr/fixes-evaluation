  This is a set of custom functions used for debugging and error handling in the Mantis Bug Tracker's SOAP webservice.

The first function, `mci_error_trace()`, is used to generate a stack trace when an error occurs. It uses XDebug or PHP's built-in `debug_backtrace()` function to retrieve the current call stack and then removes the calls to this function and the SOAP handler from the trace. The resulting array of frames is then converted into a string for display.

The second function, `mci_soap_fault_login_failed()`, creates a SOAP fault with an error code of `'Client'` and a message indicating that access was denied.

The third function, `mci_soap_fault_access_denied()`, is similar to the previous one, but it adds an additional detail message based on the provided user ID and reason for the denial.