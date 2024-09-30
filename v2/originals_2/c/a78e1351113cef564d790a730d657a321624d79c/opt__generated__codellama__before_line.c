This code is a part of the `vi` editor implementation in Unix. It defines functions for manipulating the editor's buffer, which contains the contents of the file being edited. The buffer also stores the current cursor position and other information about the state of the editor.

The `load_line()` function takes a string as input and loads it into the line buffer, which is an array of lines in the editor's buffer. It also computes the left shift required to display the entire line on the screen. If the string does not fit on the screen, it truncates the beginning of the string to fit.

The `rrshift()` function finds the maximum number of columns necessary to display the longest line in the buffer. It returns the left shift that would be needed to display the longest line.

The `color_index()` function converts an attribute (such as bold, underline, or blink) into a color index for use with the `color_map` array. The `set_color_map()` function sets the color string to use for a given attribute, and the `get_color_map()` function returns the color string to use for a given attribute.