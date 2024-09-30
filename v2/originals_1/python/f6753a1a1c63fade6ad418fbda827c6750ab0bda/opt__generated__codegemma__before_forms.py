**AnnouncementForm**

* Model form for creating announcements.
* Fields: message, category, expiry, notify.
* Widgets: MarkdownTextarea for message field, WeblateDateInput for expiry field.

**ChangesForm**

* Form for filtering changes.
* Fields: project, lang, action, user, start_date, end_date.
* Widgets: SortedSelectMultiple for action field.
* Initial data: project choices from user's allowed projects, language choices from available languages.

**LabelForm**

* Model form for creating labels.
* Fields: name, color.
* Widgets: ColorWidget for color field.

**ProjectTokenDeleteForm**

* Form for deleting project tokens.
* Fields: token.
* Initial data: token query set from the specified project.

**ProjectTokenCreateForm**

* Model form for creating project tokens.
* Fields: name, expires, project.
* Widgets: WeblateDateInput for expires field.
* Initial data: project set to the specified project.

**ProjectGroupDeleteForm**

* Form for deleting project groups.
* Fields: group.
* Initial data: group query set from the specified project.

**ProjectUserGroupForm**

* Form for managing user groups in a project.
* Fields: user, groups.
* Widgets: HiddenInput for user field, CheckboxSelectMultiple for groups field.
* Initial data: user set to the current user.

**Form Helper:**

* The `LabelForm` has a form helper that sets the form tag to `False`.

**Additional Notes:**

* The `ChangesForm` uses the `SortedSelectMultiple` widget for the action field, which may be a custom widget.
* The `WeblateDateInput` and `WeblateDateField` widgets may be custom widgets or extensions.
* The `ProjectTokenDeleteForm` and `ProjectGroupDeleteForm` have hidden input fields for the respective objects.
* The `ProjectUserGroupForm` has a hidden input field for the user field.