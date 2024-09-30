   global $config, $refresh;

   $script = basename($_SERVER['SCRIPT_NAME']);

   if ($script == 'graph_view.php' || $script == 'graph.php') {
       $refreshIsLogout = isset($_SESSION['custom']) && $_SESSION['custom'] === true ?: (isset_request_var('action') && get_nfilter_request_var('action') === 'zoom');
   } elseif (strpos($_SERVER['SCRIPT_NAME'], 'plugins') !== false) {
       $refresh = api_plugin_hook_function('top_graph_refresh', $refresh);
       $refreshIsLogout = empty($refresh);
   } else {
       $refresh = api_plugin_hook_function('top_graph_refresh', read_user_setting('page_refresh'));
       $refreshIsLogout = false;
   }

   if (isset($_SESSION['refresh'])) {
       $myrefresh['seconds'] = isset($_SESSION['refresh']['seconds']) ? $_SESSION['refresh']['seconds'] : ini_get('session.gc_maxlifetime');
       $refreshIsLogout = isset($_SESSION['refresh']['logout']) ? $_SESSION['refresh']['logout'] : true;
       $myrefresh['page'] = isset($_SESSION['refresh']['page']) ? $_SESSION['refresh']['page'] : $config['url_path'] . 'logout.php?action=timeout';
       unset($_SESSION['refresh']);
   } elseif (isset($refresh)) {
       if (is_array($refresh)) {
           $myrefresh['seconds'] = $refresh['seconds'];
           $myrefresh['page'] = $refresh['page'];
           $refreshIsLogout = false;
       } else {
           $myrefresh['seconds'] = read_user_setting('login_timeout');
           $myrefresh['page'] = $config['url_path'] . 'logout.php?action=timeout';
           $refreshIsLogout = true;
       }
   } elseif (read_user_setting('auth_method') === 0 && read_config_option('login_cookie_retention') !== 'off') {
       $myrefresh['seconds'] = 31536000; // One year in seconds
       $myrefresh['page'] = 'index.php';
       $refreshIsLogout = false;
   } else {
       $myrefresh['seconds'] = ini_get('session.gc_maxlifetime');
       $myrefresh['page'] = $config['url_path'] . 'logout.php?action=timeout';
       $refreshIsLogout = true;
   }

   // Convert boolean values to JavaScript format
   $refreshIsLogout = $refreshIsLogout ? 'true' : 'false';
   