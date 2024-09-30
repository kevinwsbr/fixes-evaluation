<?php
if (!defined("PHPWG_ROOT_PATH")) {
  die("Hacking attempt!");
}

include_once(PHPWG_ROOT_PATH . 'admin/include/functions.php');
check_status(ACCESS_ADMINISTRATOR);

$section = isset($_GET['section']) ? $_GET['section'] : '';
if (empty($section) || preg_match('/[\.\s]/', $section)) {
  die('Invalid plugin URL');
}

$sections = explode('/', $section);
for ($i = 0; $i < count($sections); $i++) {
  if (empty($sections[$i]) || $sections[$i] == '..') {
    unset($sections[$i]);
    $i--;
  }
}

if (count($sections) < 2) {
  die('Invalid plugin URL');
}

$plugin_id = $sections[0];

if (!preg_match('/^[\w-]+$/', $plugin_id)) {
  die('Invalid plugin identifier');
}

if (!isset($pwg_loaded_plugins[$plugin_id])) {
  die('Invalid URL - plugin ' . htmlspecialchars($plugin_id, ENT_QUOTES) . ' not active');
}

$filename = PHPWG_PLUGINS_PATH . implode('/', $sections);
if (is_file($filename)) {
  include_once($filename);
} else {
  die('Missing file ' . htmlspecialchars($filename, ENT_QUOTES));
}
?>
