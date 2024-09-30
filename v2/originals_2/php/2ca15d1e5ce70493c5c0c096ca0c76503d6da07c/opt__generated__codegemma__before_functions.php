$directory_path = '/path/to/directory';
$total_size = recurse_dirsize( $directory_path );

if ( $total_size !== null ) {
    echo "Total directory size: " . $total_size . " bytes";
} else {
    echo "Directory size calculation exceeded maximum execution time";
}
