  </code></pre>

This code defines the kernel module for the FarSync WAN driver. It initializes the PCI driver, allocates resources and sets up interrupts.

The `fst_add_one()` function is called when a FarSync WAN card is detected by the kernel. It does the following:

1. Allocates memory for the card structure and stores it in the array of pointers to all cards.
2. Initializes the PCI device structure with information from `pdev`.
3. Reads configuration registers of the FarSync WAN card using `fst_read_reg()`.
4. Sets up interrupt handling using `request_irq()`.
5. Allocates memory for the DMA buffers using `pci_alloc_consistent()`. This function allocates a buffer in system memory and returns a handle to the buffer in device memory. It also sets up a flag indicating whether the buffer is mapped into system memory or not. In this case, both buffers are allocated in system memory.
6. Initializes the port structures for each port on the card using `fst_init_port()`. It stores the DMA handle to the buffer in the structure and sets up a flag indicating whether the buffer is mapped into device memory or not.
7. Registers each port with the kernel using `register_hdlc_device()`.
8. Returns 0 if successful, -ENOMEM if allocation of resources failed.

The `fst_remove_one()` function is called when a FarSync WAN card is removed or disabled by the user. It does the following:

1. Unregisters each port with the kernel using `unregister_hdlc_device()`.
2. Disables interrupt handling using `free_irq()`.
3. Frees DMA buffers allocated in step 5 of `fst_add_one()` using `pci_free_consistent()`.
4. Releases memory for the card structure and sets it to NULL using `kfree()`.
5. Returns 0 if successful, -ENODEV if there is no card to remove.