// ...

// start the session
$session_name = 'phpMyAdmin';
@session_name($session_name);

if (! isset($_COOKIE[$session_name])) {
    // on first start of session we check for errors
    // f.e. session dir cannot be accessed - session file not created
    $orig_error_count = $GLOBALS['error_handler']->countErrors();
    $session_result = session_start();

    // Check if session start was successful and no errors occurred
    if ($session_result === true && $orig_error_count == $GLOBALS['error_handler']->countErrors()) {
        unset($orig_error_count, $session_result);
    } else {
        setcookie($session_name, '', 1);
        /*
         * Session initialization is done before selecting language, so we
         * can not use translations here.
         */
        PMA_fatalError(
            'Error during session start; please check your PHP and/or '
            . 'webserver log file and configure your PHP '
            . 'installation properly. Also ensure that cookies are enabled '
            . 'in your browser.'
        );
    }
} else {
    session_start();
}

// ...
