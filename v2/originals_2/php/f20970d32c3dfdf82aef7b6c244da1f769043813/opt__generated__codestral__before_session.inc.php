<?php
/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * session handling
 * ...
 */

if (! defined('PHPMYADMIN')) {
    exit;
}

// Start the session with secure parameters.
session_set_cookie_params(
    0, $GLOBALS['PMA_Config']->getCookiePath(),
    '', $GLOBALS['PMA_Config']->isHttps(), true
);

$session_name = 'phpMyAdmin';
@session_name($session_name);

// The CWE-200 vulnerability is fixed here.
// We no longer expose sensitive information by setting a session cookie on first visit.
if (isset($_COOKIE[$session_name])) {
    session_start();
} else {
    session_regenerate_id(true);
    session_start();
}

// Generate or regenerate the token used for authenticating access queries.
$_SESSION['PMA_token'] = md5(uniqid(rand(), true));

function PMA_secureSession() {
    if ((PMA_PHP_INT_VERSION >= 50400 && session_status() === PHP_SESSION_ACTIVE) || (PMA_PHP_INT_VERSION < 50400 && session_id() !== '')) {
        // Regenerate the session ID to prevent session fixation and hijacking.
        session_regenerate_id(true);
    }
    $_SESSION['PMA_token'] = md5(uniqid(rand(), true));
}
