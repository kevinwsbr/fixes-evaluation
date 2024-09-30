
This is a code snippet from the TensorFlow Lite framework. It defines three register functions for a fully connected layer:

* `Register_FULLY_CONNECTED_REF()`: This function registers the reference kernel (not optimized) for a fully connected layer.
* `Register_FULLY_CONNECTED_GENERIC_OPT()`: This function registers the generic optimized kernel for a fully connected layer.
* `Register_FULLY_CONNECTED()`: This is an alias of `Register_FULLY_CONNECTED_GENERIC_OPT()`. It is used to register the default kernel for a fully connected layer.

The kernel functions are defined in the `fully_connected` namespace and have different implementation depending on the kernel type (either reference, generic optimized or legacy PIE). The `Eval()` function is called during inference and it calls the specific implementation of the fully connected layer based on the selected kernel type.