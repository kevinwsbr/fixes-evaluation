// Create a new DV configuration box
GF_Box *dvBox = dvcC_New();

// Read DV configuration data from a bitstream
GF_Err readErr = dvcC_Read(dvBox, bitstream);

// Write DV configuration data to a bitstream
GF_Err writeErr = dvcC_Write(dvBox, bitstream);

// Free the DV configuration box
dvcC_del(dvBox);
