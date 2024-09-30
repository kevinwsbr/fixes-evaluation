**Description:**

The code snippet you provided implements a mechanism for enabling and disabling extensions in a system. It manages a list of extensions, their state, and dependencies.

**Key Functions:**

- `enableExtension(uuid)`: Enables an extension with the given UUID.
- `disableExtension(uuid)`: Disables an extension with the given UUID.
- `getEnabledExtensions()`: Returns a list of enabled extensions based on the settings and session mode.
- `onEnabledExtensionsChanged()`: Updates the list of enabled extensions when the settings change.
- `_loadExtensions()`: Loads and initializes all extensions.
- `enableAllExtensions()`: Enables all extensions.
- `disableAllExtensions()`: Disables all extensions.
- `_sessionUpdated()`: Updates the extension state based on the session mode.

**Initialization:**

- The `init()` function sets up event listeners for settings changes and session mode updates.
- It also loads and initializes all extensions.

**Features:**

- Extension discovery and loading.
- Extension state management (enabled/disabled).
- Dependency resolution for extensions.
- Session mode-based extension control.

**Usage:**

- To enable an extension, call `enableExtension(uuid)`.
- To disable an extension, call `disableExtension(uuid)`.
- To get a list of enabled extensions, call `getEnabledExtensions()`.

**Additional Notes:**

- The code assumes the presence of a `Main.sessionMode` object and a `global.settings` object.
- The `ExtensionUtils` and `extension` objects are assumed to be available globally.
- The `EXTENSION_DISABLE_VERSION_CHECK_KEY` setting is used to control version validation for extensions.