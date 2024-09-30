**UserChangeEmailSendCode:**

* The API endpoint allows users to request a code to verify their new email address.
* It receives a `schema.UserChangeEmailSendCodeReq` request.
* It checks for required fields and validates the captcha code.
* It sends an email verification code to the provided email address.
* It returns a success response with a 200 status code.

**UserChangeEmailVerify:**

* The API endpoint verifies the email verification code.
* It receives a `schema.UserChangeEmailVerifyReq` request.
* It verifies the code and sets the new email address.
* It returns a success response with a 200 status code.

**UserRanking:**

* The API endpoint provides user ranking information.
* It returns a `schema.UserRankingResp` object.
* It returns a success response with a 200 status code.

**UserUnsubscribeEmailNotification:**

* The API endpoint allows users to unsubscribe from email notifications.
* It receives a `schema.UserUnsubscribeEmailNotificationReq` request.
* It verifies the code and unsubscribes the user from email notifications.
* It returns a success response with a 200 status code.

**Key Features:**

* Email verification
* User ranking
* Email notification management

**Additional Notes:**

* The API uses authentication and authorization mechanisms to protect endpoints.
* Error handling is implemented to handle various scenarios, such as unauthorized access, expired verification codes, and ranking errors.
* The API responses are wrapped in a `handler.RespBody` object for consistency.
* The API documentation is generated using Swagger annotations.