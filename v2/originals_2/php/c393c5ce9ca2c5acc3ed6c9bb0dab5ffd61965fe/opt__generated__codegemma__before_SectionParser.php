// Parse a file and get the parsed data
$parsedData = CmsObjectParser::parse($fileContent);

// Get the markup section
$markup = $parsedData['markup'];

// Parse a file and get the line numbers where each section begins
$offsetData = CmsObjectParser::parseOffset($fileContent);

// Get the line number where the markup section begins
$markupLineNumber = $offsetData['markup'];
