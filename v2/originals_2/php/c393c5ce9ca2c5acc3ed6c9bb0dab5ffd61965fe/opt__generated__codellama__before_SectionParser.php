  This is a helper class for parsing CMS object files that use the `==` section separator to mark where the code begins and ends. The `parseOffset()` method returns an array with the line numbers of each section, which can be used to highlight the corresponding parts in the editor.

The `parse()` method takes the file content as a string argument and returns an associative array with three keys: 'settings', 'code', and 'markup'. The 'settings' key contains the contents of the first section (if any), the 'code' key contains the contents of the second section (which is assumed to contain PHP code), and the 'markup' key contains the contents of the third section (which is assumed to be HTML markup).

The `calculateLinePosition()` method calculates the line number where a specific instance of the section separator appears, and the `adjustLinePosition()` method adjusts the starting line number forward to account for opening PHP tags or whitespace that may come before the actual start of the code.

This class is used by the CMS object editor to correctly highlight the code and markup sections in an object file.