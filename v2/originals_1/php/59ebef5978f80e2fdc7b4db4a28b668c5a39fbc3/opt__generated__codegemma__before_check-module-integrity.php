<?php

$integrity_errors = array();
$external = $_GET["external"] ? true : false;

// Get the form so we can walk through its fields
$form = BigTreeAutoModule::getForm($_GET["form"]);

// Create a generic module class to get the decoded item data
$m = new BigTreeModule;
$m->Table = $form["table"];
$item = $m->get($_GET["id"]);

// Loop through all the fields
foreach ($form["fields"] as $field => $resource) {
    if ($resource["type"] == "html") {
        $integrity_errors[$field] = $admin->checkHTML("", $item[$field], $external);
    } elseif ($resource["type"] == "text" && is_string($item[$field])) {
        $href = $item[$field];
        // External link
        if (strpos($href, "http:") === 0 && strpos($href, WWW_ROOT) === false) {
            // Only check external links if we've requested them
            if ($external) {
                if (strpos($href, "#") !== false) {
                    $href = substr($href, 0, strpos($href, "#") - 1);
                }
                if (!$admin->urlExists($href)) {
                    $integrity_errors[$field] = array("a" => array($href));
                }
            }
            // Internal link
        } elseif (strpos($href, "http:") === 0) {
            if (!$admin->urlExists($href)) {
                $integrity_errors[$field] = array("a" => array($href));
            }
        }
    }
}

// Only retrieve these if we have errors as we only need them for URL generation
if (count($integrity_errors)) {
    $action = $admin->getModuleActionForForm($form);
    $module = $admin->getModule($action["module"]);
}

foreach ($integrity_errors as $field => $error_types) {
    foreach ($error_types as $type => $errors) {
        foreach ($errors as $error) {
?>
<li>
    <section class="integrity_errors">
        <a href="<?=ADMIN_ROOT . $module["route"] . "/" . $action["route"] . "/" . $_GET["id"]?>/" target="_blank">Edit</a>
        <span class="icon_small icon_small_warning"></span>
        <p>Broken <?php echo (($type == "img") ? "Image" : "Link"); ?>: <?php echo $error; ?> in field "&ldquo;<?php echo $form["fields"][$field]["title"]; ?>&rdquo;"; ?>
    </section>
</li>
<?php
        }
    }
}
?>
