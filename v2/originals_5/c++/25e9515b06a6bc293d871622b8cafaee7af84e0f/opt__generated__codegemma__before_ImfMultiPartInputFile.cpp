// Create an instance of MultiPartInputFile
MultiPartInputFile file("input_files.txt");

// Get the number of parts
int numParts = file.parts();

// Read data for part 0
InputPartData* part0Data = file.Data::getPart(0);

// Seek to chunk 10 in part 0
file.Data::seekChunk(part0Data, 10);

// Read data from the current chunk
// ...
