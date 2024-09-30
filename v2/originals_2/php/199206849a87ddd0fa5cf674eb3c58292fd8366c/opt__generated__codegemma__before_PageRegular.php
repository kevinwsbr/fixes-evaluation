**Purpose:**

The provided PHP code snippet defines a `PageRegular` class that extends a base class called `Page`. It is responsible for creating and setting up the necessary HTML and JavaScript code for a regular page.

**Key Features:**

- **Head Tags:**
    - Creates head tags for analytics scripts, user-defined head tags, and a nonce value.
- **Footer Scripts:**
    - Creates scripts for jQuery, MooTools, framework-agnostic JavaScript, and external JavaScript files.
- **JSON-LD Scripts:**
    - Provides a method to generate JSON-LD scripts based on the page's context.

**Functionality:**

The `createHeadTags()` method:

- Obtains the layout and nonce values.
- Deserializes the analytics, user head, and jQuery scripts.
- Parses the templates and concatenates the head tags.

The `createFooterScripts()` method:

- Obtains the layout and page objects (if available).
- Deserializes the MooTools, framework-agnostic, and external JavaScript scripts.
- Parses the templates and concatenates the footer scripts.
- Includes a placeholder for dynamic scripts.

**Usage:**

The `PageRegular` class is used in the Contao framework to render regular pages. It automatically generates the necessary HTML and JavaScript code based on the layout and page settings.

**Additional Notes:**

- The code uses the `FrontendTemplate` class to parse the template files.
- The `StringUtil::deserialize()` method is used to convert the serialized JavaScript and HTML code into arrays.
- The `Template::generateScriptTag()` method is used to create script tags for external JavaScript files.
- The `JsonLdManager` class is used to generate JSON-LD scripts.
- The code uses PHP's `class_alias()` function to define an alias for the `PageRegular` class.