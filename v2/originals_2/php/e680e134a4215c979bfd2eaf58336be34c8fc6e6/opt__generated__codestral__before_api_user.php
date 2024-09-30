api_expose('users/verify_email_link', function ($params) {
    if (isset($params['key']) && isset($params['user_id'])) {
        $userId = intval($params['user_id']);

        try {
            $decoded = mw()->format->decrypt($params['key']);
            if ($decoded) {
                $decoded = intval($decoded);

                // Check if the user_id in the request matches the decrypted key
                if ($userId == $decoded) {
                    $adminUser = \User::findOrFail($decoded);
                    $adminUser->is_verified = 1;
                    $adminUser->save();
                    mw()->cache_manager->delete('users');
                    mw()->cache_manager->delete('users/' . $decoded);
                    mw()->event_manager->trigger('mw.user.verify_email_link', $params);

                    return mw()->url_manager->redirect(site_url());
                } else {
                    echo "Unauthorized access";
                }
            }
        } catch (Exception $e) {
            echo 'Exception: ', $e->getMessage(), "\n";
        }
    }
});
