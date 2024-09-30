 /**
 * Display the error report page.
 * @param string $p_message The message to display at the top of the page.
 * @return null
 */
function layout_error( $p_message ) {
	global $g_log_level;

	$t_title = lang_get( 'error' );

	layout_page_header( $t_title );

	# Don't show the log level menu on error pages.
	config_set( 'show_log_level_menu', false );

	# Print out a specific error message if one was given
	if( !empty( $p_message ) ) {
		echo '<div class="alert alert-danger">' . "\n";
		echo $p_message;
		echo '</div>' . "\n";
	}

	# Print out the error report
	error_report();

	layout_footer_end();
}

/**
 * Display a database error page.
 * @param string $p_function    The name of the function where the error occurred.
 * @param string $p_file        The file in which the error was raised.
 * @param int    $p_line        The line number at which the error occurred.
 * @param string $p_description A description of the error that has occurred.
 * @return null
 */
function layout_database_error( $p_function, $p_file = __FILE__, $p_line = __LINE__, $p_description = '' ) {
	global $g_database_error;

	$t_title = lang_get( 'database_error' );

	layout_page_header( $t_title, null, false );

	# Don't show the log level menu on error pages.
	config_set( 'show_log_level_menu', false );

	# Print out a specific error message if one was given
	echo '<div class="alert alert-danger">' . "\n";
	printf( lang_get( 'database_error_description' ), $p_function, $p_file, $p_line );
	if( !empty( $g_database_error ) ) {
		echo '<br/>';
		print_language_string( 'native_database_error', null, false );
	}
	if( !empty( $p_description ) ) {
		echo '<br/>';
		echo $p_description;
	}
	echo '</div>' . "\n";

	# Print out the error report
	error_report();

	layout_footer_end();
}

/**
 * Display a database connection page.
 * @return null
 */
function layout_database_connect() {
	global $g_db;

	$t_title = lang_get( 'database' );

	layout_page_header( $t_title, null, false );

	# Don't show the log level menu on error pages.
	config_set( 'show_log_level_menu', false );

	if( db_connect() ) {
		echo '<div class="alert alert-success">';
		print_language_string( 'database_connection_established' );
		echo '</div>';

		$t_db_version = $g_db->getVersion();
		if( !empty( $t_db_version ) ) {
			echo '<p>' . sprintf( lang_get( 'database_server_version' ), $t_db_version ) . '</p>';
		}
	} else {
		layout_database_error( 'layout_database_connect()', __FILE__, __LINE__ );
	}

	layout_footer_end();
}