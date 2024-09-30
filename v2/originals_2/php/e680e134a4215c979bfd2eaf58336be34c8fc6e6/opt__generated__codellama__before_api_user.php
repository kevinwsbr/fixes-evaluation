<?php

use MicroweberPackages\Backup\Exporters\JsonExport;

api_expose('user_social_login');

api_expose('logout');

api_expose('user_register');

api_expose('social_login_process');

api_expose('user_reset_password_from_link');


api_expose_admin('user_make_logged');

api_expose('user_login');

api_expose('is_logged');

api_expose('user_send_forgot_password');


api_expose_admin('users/register_email_send_test', function () {
    try {
        mw()->option_manager->override('users', 'register_email_enabled', true);
        $send =  mw()->user_manager->register_email_send();
        if ($send) {
            $user = Auth::user();
            return 'Email is send successfully to <b>'.$user->email.'</b>.';
        }
    } catch (Exception $e) {
        echo "Error Message: <br />" . $e->getMessage();
    }
});

api_expose('users/register_email_send', function ($params = false) {
    if (!is_admin()) {
        return;
    }
    $uid = null;
    if (isset($params['user_id'])) {
        $uid = intval($params['user_id']);
    }
    if (!$uid || !User::findOrFail($uid)) {
        return;
    }
    mw()->option_manager->override('users', 'register_email_enabled', true);
    $send =  mw()->user_manager->register_email_send($uid);
    if ($send) {
        $user = User::findOrFail($uid);
        return 'Email is send successfully to <b>'.$user->email.'</b>.';
    }
});

api_expose('users/forgot_password_email_send', function ($params = false) {
    if (!is_admin()) {
        return;
    }
    $uid = null;
    if (isset($params['user_id'])) {
        $uid = intval($params['user_id']);
    }
    if (!$uid || !User::findOrFail($uid)) {
        return;
    }
    mw()->option_manager->override('users', 'forgot_password_email_enabled', true);
    $send =  mw()->user_manager->forgot_password_email_send($uid);
    if ($send) {
        $user = User::findOrFail($uid);
        return 'Email is send successfully to <b>'.$user->email.'</b>.';
    }
});

api_expose('users/search_authors', function ($params = false) {
    if (!is_admin()) {
        return;
    }
    $query = null;
    if (isset($params['query'])) {
        $query = $params['query'];
    }
    $results = User::where('email', 'like', '%'.$query.'%')->get();
    return ['status' => true, 'data' => $results];
});

api_expose('verify_email_link', function ($params = false) {
    if (!is_admin()) {
        return;
    }
    $decodedId = null;
    if (isset($params['user_id'])) {
        try {
            $decodedId = \Illuminate\Support\Facades\Crypt::decryptString($params['user_id']);
        } catch (\Exception $e) {}
    }
    if (!$decodedId || !User::findOrFail($decodedId)) {
        return;
    }
    $adminUser = User::findOrFail($decodedId);
    $adminUser->is_verified = 1;
    $adminUser->save();
    mw()->cache_manager->delete('users');
    mw()->cache_manager->delete('users/' . $decodedId);
    return ['status' => true, 'data' => ['message' => 'Email verified successfully']];
});
