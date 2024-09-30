 This code defines the controller for a user in a Go application using Gin as the web framework. The controller provides various endpoints for managing users and their email notifications. Here's a brief description of each function:

1. `UserRegister`: Registers a new user by validating the request data, checking captcha validation, adding an action record, sending a verification code to the provided email address, and handling the response.

2. `UserVerifyEmail`: Verifies the email address of a newly registered user by validating the request data, verifying the URL, updating the user's status, deleting the action record, and handling the response.

3. `GetUserInfo`: Retrieves the user's information based on the provided ID or access token, handles the response accordingly.

4. `GetUserProfile`: Fetches the user's profile data, such as answers, questions, likes, followings, and followers, and handles the response.

5. `UpdateUserInfo`: Updates the user's information based on the provided request data, validates the data, checks for captcha validation if the email address is being changed, sends a verification code to the new email address if necessary, and handles the response.

6. `UserChangeEmailVerify`: Verifies the change of email by validating the request data, checking if the URL is expired or not, verifying the user's email change request, deleting the action record, and handling the response.

7. `UserRanking`: Retrieves a list of users ranked based on their scores and handles the response.

8. `UserUnsubscribeEmailNotification`: Unsubscribes the user from receiving email notifications by validating the request data, checking if the URL is expired or not, unsubscribing the user from email notifications, and handling the response.