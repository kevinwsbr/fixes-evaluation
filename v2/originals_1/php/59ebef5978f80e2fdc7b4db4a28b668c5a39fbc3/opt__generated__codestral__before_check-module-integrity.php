$integrity_errors = array();

// Ensure that $_GET['external'] and $_GET['form'] are set before using them.
if (isset($_GET["external"])) {
    $external = filter_var($_GET["external"], FILTER_VALIDATE_BOOLEAN);
} else {
    // Handle the error appropriately, such as setting a default value or redirecting the user.
    die("Invalid request.");
}

if (isset($_GET["form"])) {
    $form = BigTreeAutoModule::getForm($_GET["form"]);
} else {
    // Handle the error appropriately, such as setting a default value or redirecting the user.
    die("Invalid form request.");
}

// Ensure that $_GET['id'] is set before using it and validate its type (int).
if (isset($_GET["id"]) && filter_var($_GET["id"], FILTER_VALIDATE_INT)) {
    $m = new BigTreeModule;
    $m->Table = $form["table"];
    $item = $m->get($_GET["id"]);
} else {
    // Handle the error appropriately, such as setting a default value or redirecting the user.
    die("Invalid item request.");
}

// Loop through all the fields
foreach ($form["fields"] as $field => $resource) {
	if ($resource["type"] == "html") {
		$integrity_errors[$field] = $admin->checkHTML("", htmlspecialchars($item[$field], ENT_QUOTES, 'UTF-8'), $external);
    // Using htmlspecialchars to prevent XSS attacks.
	} elseif ($resource["type"] == "text" && is_string($item[$field])) {
        // Use filter_var and FILTER_VALIDATE_URL to validate URLs, preventing potential SSRF attacks.
		$href = filter_var($item[$field], FILTER_SANITIZE_URL);
		if ($href !== false) {
            if (substr($href,0,4) == "http" && strpos($href,WWW_ROOT) === false) {
                if ($external) {
                    // Remove the fragment identifier from the URL before checking it.
                    $parsedUrl = parse_url($href);
                    $urlWithoutFragment = $parsedUrl['scheme'] . '://' . $parsedUrl['host'] . (isset($parsedUrl['port']) ? ':' . $parsedUrl['port'] : '') . $parsedUrl['path'];
                    if (!$admin->urlExists($urlWithoutFragment)) {
                        $integrity_errors[$field] = array("a" => array($href));
                    }
                }
            // Internal link
            } elseif (substr($href,0,4) == "http") {
                if (!$admin->urlExists($href)) {
                    $integrity_errors[$field] = array("a" => array($href));
                }
            }
        } else {
            // Handle invalid URLs appropriately.
            die("Invalid URL.");
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
        <a href="<?=ADMIN_ROOT . urlencode($module["route"]) . "/" . urlencode($action["route"]) . "/" . urlencode($_GET["id"])?>/" target="_blank">Edit</a>
        <span class="icon_small icon_small_warning"></span>
        <p>Broken <?=(($type == "img") ? "Image" : "Link")?>: <?=htmlspecialchars($error, ENT_QUOTES, 'UTF-8')?> in field &ldquo;<?=htmlspecialchars($form["fields"][$field]["title"], ENT_QUOTES, 'UTF-8')?>&rdquo;</p>
    </section>
</li>
<?php
        }
	}
}
?>
