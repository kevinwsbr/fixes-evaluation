<?php
/*
   This file is part of Webfinance.

    Webfinance is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Webfinance is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

// Require secure communication protocol
if (!isset($_SERVER['HTTPS']) || $_SERVER['HTTPS'] !== 'on') {
    // Redirect to HTTPS version of web page
    header("Location: https://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI']);
    exit();
}

// Include file with error handling mechanism
require('../inc/main.php');

// Check for session fixation attack
session_regenerate_id(true);

// Validate user input
$input = filter_input(INPUT_POST, 'tax_rate', FILTER_SANITIZE_NUMBER_FLOAT, FILTER_FLAG_ALLOW_THOUSAND | FILTER_FLAG_ALLOW_SCIENTIFIC);
if (!is_numeric($input)) {
    // Return error message if input is not numeric
    echo 'Invalid tax rate!';
    exit();
} else {
    // Sanitize and validate user input
    $taxRate = filter_var($input, FILTER_SANITIZE_NUMBER_FLOAT, FILTER_FLAG_ALLOW_THOUSAND | FILTER_FLAG_ALLOW_SCIENTIFIC);
}

// Connect to database and perform query
$db = new PDO('mysql:host=localhost;dbname=mydatabase', 'username', 'password');
$statement = $db->prepare("UPDATE tax_rates SET rate = :rate WHERE id = :id");
$statement->bindParam(':rate', $taxRate, PDO::PARAM_STR);
$statement->bindParam(':id', $_SESSION['user']['id'], PDO::PARAM_INT);
$statement->execute();

// Redirect user to home page
header("Location: /");
exit();
