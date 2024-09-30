 The provided code snippet is part of a larger PHP script that likely belongs to a web application. It appears to be handling the management and display of language data, including visibility settings, edit options, and sub-language management for each language entry. Below, I'll break down the key components and functionalities of this script:

### Key Components and Functionalities

1. **Security::remove_XSS()**: This function is used to sanitize input by removing any potentially harmful scripts or HTML tags from user inputs, which helps in preventing XSS (Cross-Site Scripting) attacks.

2. **Display::return_icon()**: This helper function returns an HTML string for an icon with optional title text and attributes. It's used here to display icons like arrows and edit options.

3. **Security::remove_XSS() in URLs**: The script uses `Security::remove_XSS()` multiple times within URL parameters, ensuring that any potentially malicious data is removed before being processed by the server.

4. **Sub-language Management**:
   - **`$allow_use_sub_language`**: A link to add words for a sub-language.
   - **`$allow_add_term_sub_language`**: Another link related to adding terms or words for the sub-language.
   - **`$allow_delete_sub_language`**: A link to delete the sub-language, if available.

5. **Visibility and Invisibility Control**:
   - The script allows toggling visibility of language entries using `makeavailable` and `makeunavailable` actions. It uses JavaScript or AJAX requests (not explicitly shown in the snippet) to update the visibility status without reloading the page.

6. **Table Display**:
   - A `SortableTableFromArrayConfig` object is used to display the language data in a table format, with options for sorting and action forms like making content visible or invisible.
   - The table includes columns for original name, English name, LMS folder, and properties (with icons and links as described).

7. **Form Actions**:
   - An array `$form_actions` defines possible actions (`makeavailable` and `makeunavailable`) that can be performed on the language entries. These are used in forms or buttons for user interaction.

### PHP Code Breakdown

- **HTML Output**: The script outputs HTML, including anchor tags (`<a>`) and icon images (`<img>`), which are embedded within strings using `Display::return_icon()` and similar functions.
- **Conditional Rendering**: Many elements (like visibility icons and action links) are conditionally rendered based on the state of each language entry (e.g., whether it's visible or not, if sub-languages exist).
- **JavaScript/AJAX Usage**: Although AJAX is not explicitly mentioned in the snippet, parts of the script suggest dynamic content updates without reloading the page. This likely involves JavaScript for handling actions like toggling visibility states.

### Conclusion

This PHP script effectively manages and presents language data with various interactive features including sub-language management and visibility controls. It uses a combination of HTML output, conditional logic, and client-side interactions (possibly via AJAX) to provide an intuitive interface for editing and managing language entries within the application.