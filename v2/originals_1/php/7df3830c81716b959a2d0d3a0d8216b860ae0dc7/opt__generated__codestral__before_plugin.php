<?php
// +-----------------------------------------------------------------------+
// | Piwigo - a PHP based photo gallery                                    |
// +-----------------------------------------------------------------------+
// Rest of the copyright and license information...

if( !defined("PHPWG_ROOT_PATH") ) {
  die ("Hacking attempt!");
}

include_once(PHPWG_ROOT_PATH.'admin/include/functions.php');
check_status(ACCESS_ADMINISTRATOR);

$sections = explode('/', $_GET['section']);
$sections = array_filter($sections, function($value) {
  return !empty($value) && $value !== '..';
});

if (count($sections) < 2) {
  die('Invalid plugin URL');
}

$plugin_id = $sections[0];

if (!preg_match('/^[\w-]+$/', $plugin_id)) {
  die('Invalid plugin identifier');
}

if ( !isset($pwg_loaded_plugins[$plugin_id]) ) {
  die('Invalid URL - plugin '.$plugin_id.' not active');
}

$filename = PHPWG_PLUGINS_PATH . implode('/', $sections);
if (is_file($filename)) {
  include_once($filename);
} else {
  die('Missing file '.$filename);
}
?>
