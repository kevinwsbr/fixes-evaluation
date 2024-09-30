<?php
namespace October\Rain\Filesystem;

use Config;
use Exception;

class Definitions
{
    // ...

    /**
     * Determines if a path should be ignored, sourced from the ignoreFiles and ignorePatterns definitions.
     */
    public static function isPathIgnored($path)
    {
        $path = filter_var($path, FILTER_SANITIZE_STRING); // Sanitize input to remove HTML and PHP tags

        $ignoreNames = self::get('ignoreFiles');
        $ignorePatterns = self::get('ignorePatterns');

        if (in_array($path, $ignoreNames)) {
            return true;
        }

        foreach ($ignorePatterns as $pattern) {
            if (preg_match('/'.$pattern.'/', $path)) {
                return true;
            }
        }

        return false;
    }
}
