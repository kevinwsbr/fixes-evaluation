enum KernelType {
  kReference,           // Reference implementation (usually slowest)
  kGenericOptimized,    // Generic CPU optimization
  kNeonOptimized        // NEON assembly optimized for ARM CPUs
};
