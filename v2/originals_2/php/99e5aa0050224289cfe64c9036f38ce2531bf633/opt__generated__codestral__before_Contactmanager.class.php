// Include the class file if it hasn't been already
require_once('path/to/CountryCodes.php');

$countryCode = "US"; // United States
$countryName = CountryCodes::$codes[$countryCode];
echo $countryName;  // Outputs: United States
