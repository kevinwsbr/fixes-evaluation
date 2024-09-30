// Create a XlaCompilationCache.
XlaCompilationCache cache(client, DEVICE_GPU);

// Create an XlaPlatformInfo object.
XlaPlatformInfo platform_info = XlaPlatformInfoFromDevice(device);

// Generate compiler options.
XlaCompiler::Options options = GenerateCompilerOptions(cache, function_library, device, nullptr, platform_info, false);

// Compile the XLA graph.
Status status = compiler.Compile(options);
