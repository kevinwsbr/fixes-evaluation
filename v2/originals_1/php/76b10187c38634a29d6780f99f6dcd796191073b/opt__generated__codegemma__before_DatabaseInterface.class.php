// Create a new PMALink object
$db = new PMALink();

// Execute a query and get the result set
$result = $db->query('SELECT * FROM users');

// Get the length of the first field in the result set
$field_length = $db->fieldLen($result, 0);

// Close the result set
$db->freeResult($result);
