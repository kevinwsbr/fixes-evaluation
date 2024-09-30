<?php
if (!empty($_POST['url'])) {
    $input_url = $_POST['url'];
    if (filter_var($input_url, FILTER_VALIDATE_URL) !== false) {
        $url = filter_var($input_url, FILTER_SANITIZE_URL);
    } else {
        echo "Invalid URL";
        exit;
    }
} else {
    $url = '';
}
// rest of the code...
