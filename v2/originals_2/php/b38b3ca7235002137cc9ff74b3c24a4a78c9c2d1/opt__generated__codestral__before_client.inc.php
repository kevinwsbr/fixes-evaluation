<?php
/*********************************************************************
    client.inc.php

    File included on every client page

    Peter Rotich <peter@osticket.com>
    Copyright (c)  2006-2013 osTicket
    http://www.osticket.com

    Released under the GNU General Public License WITHOUT ANY WARRANTY.
    See LICENSE.TXT for details.

    vim: expandtab sw=4 ts=4 sts=4:
**********************************************************************/
if(basename($_SERVER['SCRIPT_NAME']) === basename(__FILE__)) {
    die('kwaheri rafiki!');
}

$thisdir = str_replace('\\', '/', dirname(__FILE__)).'/';
if(!file_exists($thisdir.'main.inc.php')) {
    http_response_code(500); // Internal Server Error
    die('Fatal Error.');
}

require_once($thisdir.'main.inc.php');

if(!defined('INCLUDE_DIR')) {
    http_response_code(500); // Internal Server Error
    die('Fatal error');
}

/* Some more include defines specific to client only */
define('CLIENTINC_DIR', INCLUDE_DIR.'client/');
define('OSTCLIENTINC', true);

define('ASSETS_PATH', ROOT_PATH.'assets/default/');

// Check the status of the HelpDesk.
if (!in_array(strtolower(basename($_SERVER['SCRIPT_NAME'])), ['logo.php']) && !(is_object($ost) && $ost->isSystemOnline())) {
    include(ROOT_DIR.'offline.php');
    exit;
}

/* Include what is needed on client stuff */
require_once(INCLUDE_DIR.'class.client.php');
require_once(INCLUDE_DIR.'class.ticket.php');
require_once(INCLUDE_DIR.'class.dept.php');

// Clear some vars
$errors = [];
$msg = '';
$nav = null;

// Make sure the user is valid before doing anything else.
$thisclient = UserAuthenticationBackend::getUser();

if (isset($_GET['lang']) && !empty($_GET['lang'])) {
    $_SESSION['client:lang'] = filter_input(INPUT_GET, 'lang', FILTER_SANITIZE_STRING);
}

// Bootstrap gettext translations as early as possible, but after attempting to sign on the agent
TextDomain::configureForUser($thisclient);

// Is the user logged in?
if ($thisclient && $thisclient->getId() && $thisclient->isValid()) {
    $thisclient->refreshSession();
} else {
    $thisclient = null;
}

/******* CSRF Protection *************/
// Enforce CSRF protection for POSTS
if ($_POST && !$ost->checkCSRFToken()) {
    header('Location: index.php');
    exit; // Added exit() to ensure that no further code execution occurs after the redirect
}

// Add token to the header - used on AJAX calls [DO NOT CHANGE THE NAME]
$ost->addExtraHeader('<meta name="csrf_token" content="'.$ost->getCSRFToken().'" />');

/* Client specific defaults */
define('PAGE_LIMIT', DEFAULT_PAGE_LIMIT);

$nav = new UserNav($thisclient, 'home');

$exempt = in_array(basename($_SERVER['SCRIPT_NAME']), ['logout.php', 'ajax.php', 'logs.php', 'upgrade.php']);

if (!$exempt && $thisclient && ($acct = $thisclient->getAccount()) && $acct->isPasswdResetForced()) {
    $warn = __('Password change required to continue');
    require_once('profile.php'); // profile.php must be included as once to avoid problems.
    exit;
}
?>
