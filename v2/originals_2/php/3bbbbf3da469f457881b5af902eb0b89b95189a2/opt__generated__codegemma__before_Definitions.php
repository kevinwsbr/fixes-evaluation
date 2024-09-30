/**
 * Determines if a path should be ignored, sourced from the ignoreFiles 
 * and ignorePatterns definitions.
 * @todo Efficiency of this method can be improved.
 * @param string $path Specifies a path to check.
 * @return boolean Returns TRUE if the path is visible.
 */
public static function isPathIgnored($path)
{
    $ignoreNames = self::get('ignoreFiles');
    $ignorePatterns = self::get('ignorePatterns');

    if (in_array($path, $ignoreNames)) {
        return true;
    }

    foreach ($ignorePatterns as $pattern) {
        if (preg_match('/'.e($pattern).'/', $path)) { // Corrected line using e() function
            return true;
        }
    }

    return false;
}
