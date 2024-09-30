<?php
$bigtree = new BigTree();

// Get the current user's data
$user = $bigtree->getCurrentUser();
print_r($user);

// Update the user's email address
$bigtree->updateUserEmail("new@example.com");
