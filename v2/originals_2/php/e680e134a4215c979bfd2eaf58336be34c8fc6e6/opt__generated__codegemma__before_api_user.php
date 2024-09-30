
api_expose('users/register_email_send', function ($params = false) {
    $uid = null;
    if (isset($params['user_id']) and is_admin()) {
        $uid = intval($params['user_id']);
    }

    if (!is_admin()) {
        throw new Exception('Unauthorized access.');
    }

    return mw()->user_manager->register_email_send($uid);
});

api_expose('users/forgot_password_email_send_test', function () {

     try {
         $user = Auth::user();

         if (!$user->is_admin()) {
             throw new Exception('Unauthorized access.');
         }

         mw()->option_manager->override('users', 'forgot_pass_email_enabled', true);
         $send = mw()->user_manager->send_forgot_password([
             'email'=>$user->email
         ]);
         if ($send) {
             return 'Email is send successfully to <b>'.$user->email.'</b>.';
         }
    } catch (Exception $e) {
        echo "Error Message: <br />" . $e->getMessage();
    }

});

