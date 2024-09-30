// Create an instance of the LinkElement class
$link = new LinkElement();

// Set the data from the edit mode form
$link->setDataFromEditmode($data);

// Get the class of the link
echo $link->getClass();

// Get the attributes of the link
echo $link->getAttributes();
