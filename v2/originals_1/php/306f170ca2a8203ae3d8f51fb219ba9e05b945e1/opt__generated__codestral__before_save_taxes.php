<?php
// This file is part of « Webfinance »
// ...

require("../inc/main.php");
must_login();

if ($_GET['action'] === "delete") {
  $id = mysqli_real_escape_string($db, $_GET['id']);
  $query = "DELETE FROM webfinance_pref WHERE id_pref=$id";
  if(mysqli_query($conn, $query)) {
    $_SESSION['message'] = _('Tax deleted');
  } else {
    // Handle the error appropriately
  }
  header("Location: preferences.php?tab=Taxes");
  exit;
}

foreach ($_POST['taxes'] as $id => $data) {
  $taxe = mysqli_real_escape_string($db, $data['taxe']);
  $value = mysqli_real_escape_string($db, $data['value']);

  if ($id === "new") {
    if (!empty($taxe)) {
      $query = "INSERT INTO webfinance_pref (type_pref, value) VALUES ('taxe_$taxe', '$value')";
      $_SESSION['message'] = _('Tax added');
    }
  } else {
    $query = "UPDATE webfinance_pref SET type_pref='taxe_$taxe', value='$value' WHERE id_pref=$id ";
    $_SESSION['message'] = _('Tax updated');
  }

  if(isset($query) && !empty($query)) {
    if(!mysqli_query($conn, $query)) {
      // Handle the error appropriately
    }
  }
}

header("Location: preferences.php?tab=Taxes");
exit;
?>
