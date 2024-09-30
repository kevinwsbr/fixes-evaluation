 This code is a part of an editor written in C. It handles loading and displaying strings on the screen, managing the line buffer, and dealing with colors. Here's a brief explanation:

1. `pappstr(str)`: This function checks if a string can fit on the screen. If not, it returns 1; otherwise, it returns 0. The `while (*str != '\0')` loop iterates through each character in the string until it reaches the end of the string (represented by `'\0'`).

2. `load_line(str)`: This function loads a string into the line buffer. If the string is too long to fit on the screen, it truncates the beginning of the string to fit. It does this by repeatedly calling `prewind()` (which rewinds the line buffer) and `pappstr(str)`. If the string doesn't fit, it increases the left shift by one and tries again.

3. `rrshift()`: This function finds the necessary shift to display the end of the longest displayed line. It temporarily sets the screen width to the maximum integer value, then iterates through each line on the screen and keeps track of the length of the longest line. Finally, it calculates the difference between this length and the screen width, which is the amount by which the screen needs to be shifted right to display the end of the longest line.

4. `color_index(attr)`: This function takes an attribute as input and returns the index in the color map associated with that attribute. The color map is an array of strings that store the color settings for different attributes.

5. `set_color_map(attr, colorstr)`: This function sets the color string to use for a given attribute. It first checks if the input attribute and color string are valid, then copies the color string into the appropriate slot in the color map array.

6. `get_color_map(attr)`: This function returns the color string associated with a given attribute.