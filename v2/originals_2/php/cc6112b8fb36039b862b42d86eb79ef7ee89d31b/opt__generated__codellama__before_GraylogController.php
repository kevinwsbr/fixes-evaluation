// ...
$stream = $request->query('stream'); // This should be validated
$device = $request->query('device'); // This should be sanitized
$range = $request->query('range'); // This should be validated and sanitized
$limit = $request->query('limit'); // This should be validated
$offset = $request->query('offset'); // This should be validated
$sort = $request->query('sort'); // This should be validated and sanitized
// ...
