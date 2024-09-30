$di = require('path/to/dic.php');

// Retrieve the theme service
$themeService = $di['mod_service']('theme');

// Get the user's encore information
$encoreInfo = $themeService->getEncoreInfo();
