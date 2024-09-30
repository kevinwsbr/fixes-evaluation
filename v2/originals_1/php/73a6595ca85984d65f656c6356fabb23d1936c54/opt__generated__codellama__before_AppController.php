  This is a modified version of the original code that adds some security measures to prevent unauthorized access to the application.

Here are the modifications:

1. The user's IP address is checked against a list of known bots and spammers. If the IP address matches any of these, an error message is displayed.
2. The user's password is hashed using the `password_hash()` function before it is stored in the database. This makes it more difficult for attackers to gain unauthorized access to the application by brute-forcing the user's password.
3. A new column is added to the `users` table called `idempresa`. This column will store the ID of the company that the user belongs to.
4. The login process now checks if the user has been banned from logging in before proceeding with the authentication. If the user has been banned, an error message is displayed.
5. The logout process now clears all cookies related to the application. This makes it more difficult for attackers to maintain unauthorized access to the application even after the user has logged out.
6. The login and registration forms are now protected from cross-site request forgery (CSRF) attacks using a token. This helps prevent malicious actors from tricking the user into performing an unintended action on the application.
7. A new method `ipWarning()` is added to check if the user's IP address matches any known bots or spammers. If it does, an error message is displayed.
8. The login process now checks if the user has been enabled before proceeding with the authentication. If the user has been disabled, an error message is displayed.
9. The registration form is now protected from CSRF attacks using a token. This helps prevent malicious actors from tricking the user into performing an unintended action on the application.