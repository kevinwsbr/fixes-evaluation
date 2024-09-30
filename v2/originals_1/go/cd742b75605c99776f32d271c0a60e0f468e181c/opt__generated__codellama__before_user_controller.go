
[PYTHON]
class UserController:
    def __init__(self, user_service: UserService, email_service: EmailService):
        self.user_service = user_service
        self.email_service = email_service

    def UserChangeEmail(self, ctx: gin.Context):
        req = UserChangeEmailReq()
        if handler.BindAndCheck(ctx, req):
            return

        captcha_pass = self.action_service.ActionRecordVerifyCaptcha(
            ctx, schema.ActionRecordTypeEmail, ctx.ClientIP(), req.captcha_id, req.captcha_code)
        if not captcha_pass:
            err_fields = [
                validator.FormErrorField(error_field="captcha_code", error_msg=translator.Tr(handler.GetLang(ctx), reason.CaptchaVerificationFailed))
            ]
            handler.HandleResponse(ctx, errors.BadRequest(reason.CaptchaVerificationFailed), err_fields)
            return

        _, _ = self.action_service.ActionRecordAdd(ctx, schema.ActionRecordTypeEmail, ctx.ClientIP())
        resp, err = self.user_service.UserChangeEmailSendCode(ctx, req)
        if err is not None:
            handler.HandleResponse(ctx, err, resp)
            return

        handler.HandleResponse(ctx, err, None)

    def UserChangeEmailVerify(self, ctx: gin.Context):
        req = UserChangeEmailVerifyReq()
        if handler.BindAndCheck(ctx, req):
            return

        req.content = self.email_service.VerifyUrlExpired(ctx, req.code)
        if len(req.content) == 0:
            handler.HandleResponse(ctx, errors.Forbidden(reason.EmailVerifyURLExpired),
                    schema.ForbiddenResp(schema.ForbiddenReasonTypeURLExpired))
            return

        err = self.user_service.UserChangeEmailVerify(ctx, req.content)
        self.action_service.ActionRecordDel(ctx, schema.ActionRecordTypeEmail, ctx.ClientIP())
        handler.HandleResponse(ctx, err, None)

    def UserRanking(self, ctx: gin.Context):
        resp, err = self.user_service.UserRanking(ctx)
        handler.HandleResponse(ctx, err, resp)

    def UserUnsubscribeEmailNotification(self, ctx: gin.Context):
        req = UserUnsubscribeEmailNotificationReq()
        if handler.BindAndCheck(ctx, req):
            return

        req.content = self.email_service.VerifyUrlExpired(ctx, req.code)
        if len(req.content) == 0:
            handler.HandleResponse(ctx, errors.Forbidden(reason.EmailVerifyURLExpired),
                    schema.ForbiddenResp(schema.ForbiddenReasonTypeURLExpired))
            return

        err = self.user_service.UserUnsubscribeEmailNotification(ctx, req)
        handler.HandleResponse(ctx, err, None)
[/PYTHON]
