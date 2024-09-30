**Changes:**

* The code has been reorganized and refactored to improve readability and maintainability.
* Added a new class `CairoSurfaceLoader` to handle image loading and surface creation.
* Updated the `AboutDialog` class to set the program name based on whether the application is built as a flatpak.
* Modified the `WarpLogFormatter` class to define different log formats for debug, error, and info messages.
* Created a new function `add_to_recents_if_single_selection()` to add a single file to the recent files list.
* Implemented a new function `get_recent_chooser_menu()` to create a GtkRecentChooserMenu widget.

**Improvements:**

* Enhanced logging capabilities with different log formats.
* Improved user interface with the `AboutDialog` and recent files menu.
* Enhanced file management with the `CairoSurfaceLoader` class.

**Additional Notes:**

* The code includes configuration options and constants that are not shown in the provided snippet.
* The specific implementation of the `config` module is not included.
* The `Gtk` and `Gdk` libraries are assumed to be imported.