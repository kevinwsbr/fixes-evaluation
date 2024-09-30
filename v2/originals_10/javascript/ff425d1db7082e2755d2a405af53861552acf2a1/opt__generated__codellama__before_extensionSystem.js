This is an example of a JavaScript class in the Extension system of GNOME, which manages the loading and unloading of extensions.
The `ExtensionUtils` namespace provides methods for working with extensions, such as `getEnabledExtensions()` and `loadExtension()`.
The `ExtensionModule` object represents a loaded extension, with properties for its metadata (such as its name and version) and its state (whether it is enabled or disabled).
The `enableAllExtensions()` method enables all extensions that are currently enabled in the system, while the `disableAllExtensions()` method disables all extensions.
The `_sessionUpdated()` method updates the extension manager's internal state based on changes to the system session settings, such as whether the user has allowed extensions or not.
The `init()` method sets up event handlers for session mode updated and enabled extensions changed events.