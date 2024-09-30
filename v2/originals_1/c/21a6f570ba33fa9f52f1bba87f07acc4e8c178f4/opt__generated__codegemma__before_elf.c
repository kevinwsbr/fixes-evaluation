// Load an ELF file
ELFOBJ *bin = Elf_(r_bin_elf_new)("path/to/file", false);

// Print the base address of the program
printf("Base address: %lx\n", bin->baddr);

// Convert a physical address to a virtual address
ut64 vaddr = Elf_(r_bin_elf_p2v)(bin, phys_addr);

// Print the virtual address
printf("Virtual address: %lx\n", vaddr);
