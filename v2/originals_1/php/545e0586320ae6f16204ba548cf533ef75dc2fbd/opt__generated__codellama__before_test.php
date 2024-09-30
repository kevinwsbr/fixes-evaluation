<?php
/**
 * test.php
 *
 * @author iubenda s.r.l
 * @copyright 2018-2020, iubenda s.r.l
 * @license GNU/GPL
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

// check if the input is a valid URL
if (!filter_var($url, FILTER_VALIDATE_URL)) {
    die("Invalid URL");
}

$content = file_get_contents($url);

// parse the content using the iubendaParser class
$iubenda = new iubendaParser($content);
$iubenda->parse();

// output the results
echo "Iubenda comments detected: " . count($iubenda->iub_comments_detected) . "<br>";
echo "Iubenda automatic stuff detected: " . count($iubenda->stuff_detected) . "<br>";
echo "Scripts detected: " . count($iubenda->scripts_detected) . "<br>";
echo "Scripts converted: " . count($iubenda->scripts_converted) . "<br>";
echo "Inline scripts detected: " . count($iubenda->scripts_inline_detected) . "<br>";
echo "Inline scripts converted: " . count($iubenda->scripts_inline_converted) . "<br>";
