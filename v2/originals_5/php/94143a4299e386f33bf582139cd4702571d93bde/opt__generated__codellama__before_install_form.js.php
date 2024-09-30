<?php
// Add sanitization and validation for user-supplied input
header('Content-type: text/javascript');
$ftp_host = filter_var($_POST['ftp_host'], FILTER_SANITIZE_STRING);
$ftp_username = filter_var($_POST['ftp_username'], FILTER_SANITIZE_STRING);
$ftp_password = filter_var($_POST['ftp_password'], FILTER_SANITIZE_STRING);
$ftp_path = filter_var($_POST['ftp_path'], FILTER_SANITIZE_STRING);
$database_name = filter_var($_POST['database_name'], FILTER_SANITIZE_STRING);
$mysql_user = filter_var($_POST['mysql_user'], FILTER_SANITIZE_STRING);
$mysql_password = filter_var($_POST['mysql_password'], FILTER_SANITIZE_STRING);

// Add validation for user-supplied input
if (!in_array($ftp_host, ['localhost', '127.0.0.1'])) {
  // Handle invalid FTP host input
}

if (!in_array($database_name, ['my_database'])) {
  // Handle invalid database name input
}

// Sanitize output using htmlspecialchars()
echo "<div id='ftp-test-results'>";
echo htmlspecialchars($result['message']);
echo "</div>";

echo "<div id='db-test-results'>";
echo htmlspecialchars($result['message']);
echo "</div>";
?>
