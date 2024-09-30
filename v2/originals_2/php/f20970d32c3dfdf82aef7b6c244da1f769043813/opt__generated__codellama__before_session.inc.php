<?php
/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * session handling
 *
 * @todo    add failover or warn if sessions are not configured properly
 * @todo    add an option to use mm-module for session handler
 *
 * @package PhpMyAdmin
 * @see     http://www.php.net/session
 */
if (! defined('PHPMYADMIN')) {
    exit;
}

// verify if PHP supports session, die if it does not

if (!@function_exists('session_name')) {
    PMA_warnMissingExtension('session', true);
} elseif (ini_get('session.auto_start') !== '' && session_name() != 'phpMyAdmin') {
    // Do not delete the existing session, it might be used by other
    // applications; instead just close it.
    session_write_close();
}

// disable starting of sessions before all settings are done
// does not work, besides how it is written in php manual
//ini_set('session.auto_start', '0');

// session cookie settings
session_set_cookie_params(
    0, $GLOBALS['PMA_Config']->getCookiePath(),
    '', $GLOBALS['PMA_Config']->isHttps(), true
);

// cookies are safer (use @ini_set() in case this function is disabled)
@ini_set('session.use_cookies', 'true');

// optionally set session_save_path
$path = $GLOBALS['PMA_Config']->get('SessionSavePath');
if (!empty($path)) {
    session_save_path($path);
}

// but not all user allow cookies
@ini_set('session.use_only_cookies', 'false');

/**
 * Token which is used for authenticating access queries.
 * (we use "space PMA_token space" to prevent overwriting)
 */
if (! isset($_SESSION[' PMA_token '])) {
    $_SESSION[' PMA_token '] = md5(uniqid(rand(), true));
}

/**
 * tries to secure session from hijacking and fixation
 * should be called before login and after successful login
 * (only required if sensitive information stored in session)
 *
 * @return void
 */
function PMA_secureSession()
{
    // prevent session fixation and XSS
    // (better to use session_status() if available)
    if ((PMA_PHP_INT_VERSION >= 50400 && session_status() === PHP_SESSION_ACTIVE)
        || (PMA_PHP_INT_VERSION < 50400 && session_id() !== '')
    ) {
        session_regenerate_id(true);
    }
    $_SESSION[' PMA_token '] = md5(uniqid(rand(), true));
}
