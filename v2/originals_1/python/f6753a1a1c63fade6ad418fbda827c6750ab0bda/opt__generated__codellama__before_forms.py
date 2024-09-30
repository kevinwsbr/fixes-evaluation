
This is an example of a Django form that includes multiple fields and has custom validation rules. The `ChangesForm` class defines two models, `ProjectTokenDeleteForm` and `ProjectTokenCreateForm`, which are used to delete and create token objects associated with a project. The `LabelForm` class is used to manage labels associated with a project.

The `UserManageForm` class is also included in this example as it has custom validation rules for managing users and groups associated with a project.

The `__init__` method of each form class is called when the form is instantiated, and it sets up the initial values for the fields, adds custom validators or widgets to the fields, and so on.

In this example, we use the `ModelChoiceField` class from Django to create a drop-down menu for selecting a project or a token object associated with a project. We also use the `MultipleChoiceField` class to create a checkbox list for selecting multiple groups.

We also define custom validation rules for each form class, such as making sure that the user is an authorized user for the selected project in the `UserManageForm` class.

It's important to note that this is just one example of how you can use Django forms, and there are many other ways to create forms with custom validation rules and functionality.