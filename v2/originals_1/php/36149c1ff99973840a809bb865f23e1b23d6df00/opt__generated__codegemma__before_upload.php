$doc = new stdClass();
$doc->title = 'My File';
$filePath = '/path/to/file.pdf';
$courseId = 1;

upload_file($doc, $filePath, $courseId);
