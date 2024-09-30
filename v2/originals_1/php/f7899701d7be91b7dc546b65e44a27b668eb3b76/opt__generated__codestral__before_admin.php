 The `User` class is a part of the BigTree CMS framework. It provides methods to interact with user data in the database and perform various operations such as creating, updating, and deleting users. Here's a breakdown of some key functionalities:

1. **createUser**: This method creates a new user with the provided name, email, password, level, permissions, alerts, and daily digest options. It checks if the user already exists by email, generates a hashed password using the PHPass library, and inserts the new user into the database.

2. **updateUser**: This method updates an existing user's information based on their ID. It allows updating the name, level, permissions, alerts, and daily digest options for the specified user.

3. **updateUserPassword**: This method updates a user's password by hashing the new password using PHPass and storing it in the database.

4. **validatePassword**: This method validates a password against the security policy defined in the BigTree CMS configuration. It checks for length, case sensitivity, numeric characters, and non-alphanumeric characters based on the policies set.

5. **verifyCSRFToken**: This method verifies the referring host and session token to prevent cross-site request forgery attacks. It compares the cleaned referrer with the cleaned domain and checks if the provided CSRF token matches the generated one in the session.

6. **versionToDecimal**: This static method converts a BigTree version number (e.g., 4.2.0) into a decimal number for easy comparison. It breaks down the version number into its major, minor, and patch components and calculates the decimal value accordingly.