// Create a sample data structure
$data = [
    'name' => 'John Doe',
    'email' => 'john@example.com',
    'birthdate' => time(),
];

// Encode the data into XML
$xml = eZContentXMLWriter::xmlEncode($data);

// Print the XML string
echo $xml;
