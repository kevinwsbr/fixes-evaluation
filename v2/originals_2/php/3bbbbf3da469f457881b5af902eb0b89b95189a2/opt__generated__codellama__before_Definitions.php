<?php namespace October\Rain\Filesystem;

use Config;
use Exception;

/**
 * File definitions helper.
 * Contains file extensions for common use cases.
 *
 * @package october\filesystem
 * @author Alexey Bobkov, Samuel Georges
 */
class Definitions
{
    /**
     * Entry point to request a definition set.
     * @param $type string
     * @return array
     */
    public static function get($type)
    {
        return (new self)->getDefinitions($type);
    }

    /**
     * Returns a definition set from config or from the default sets.
     * @param $type string
     * @return array
     */
    public function getDefinitions($type)
    {
        if (!method_exists($this, $type)) {
            throw new Exception(sprintf('No such definition set exists for "%s"', $type));
        }

        return (array) Config::get('cms.fileDefinitions.'.$type, $this->$type());
    }

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
            if (preg_match('/'.$pattern.'/', $path)) {
                return true;
            }
        }

        return false;
    }

    /**
     * Files that can be safely ignored.
     * @return array
     */
    protected function ignoreFiles()
    {
        return ['.htaccess', 'index.php'];
    }

    /**
     * Patterns for ignoring files and directories.
     * @return array
     */
    protected function ignorePatterns()
    {
        return ['/\/vendor\//', '/config\/.*\.php$/'];
    }

    /**
     * Extensions seen as public assets.
     * @return array
     */
    protected function assetExtensions()
    {
        return [
            'jpg',
            'jpeg',
            'bmp',
            'png',
            'webp',
            'gif',
            'ico',
            'css',
            'js',
            'woff',
            'woff2',
            'svg',
            'ttf',
            'eot',
            'json',
            'md',
            'less',
            'sass',
            'scss'
        ];
    }

    /**
     * Extensions typically used as images.
     * @return array
     */
    protected function imageExtensions()
    {
        return [
            'jpg',
            'jpeg',
            'bmp',
            'png',
            'webp',
            'gif',
            'svg'
        ];
    }

    /**
     * Extensions typically used as video files.
     * @return array
     */
    protected function videoExtensions()
    {
        return [
            'mp4',
            'avi',
            'mov',
            'mpg',
            'mpeg',
            'mkv',
            'webm'
        ];
    }

    /**
     * Extensions typically used as audio files.
     * @return array
     */
    protected function audioExtensions()
    {
        return [
            'mp3',
            'wav',
            'wma',
            'm4a',
            'ogg'
        ];
    }
}
