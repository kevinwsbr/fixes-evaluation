 <?php

$config = mw()->getConfig();

$params['id'] = $params['data-id'];
$mw_live_edit_module_settings_url = admin_url() . 'view:admin/tools/#mw_live_edit_module_settings';

if (isset($params['module']) and isset($params['module'])) {
    $mod_class = get_class(get_class_by_full_name($params['module']));
} else if ($params['id']) {
    $mod_class = get_class_by_id($params['id']);
}
if (empty($mod_class)) {
    return;
}

$data_live_edit = '';

$data_type = 'data-type';

if ($mod_class == false) {
    $mod_class = 'modules/' . strtolower($params['module']);
}

if (isset($params['settings']) && !empty($params['settings'])) {
    $mpar = array('id' => $params['id'], 'module' => $params['module'], 'settings' => json_decode($params['settings']));
    if (!is_object($mpar['settings'])) {
        $mpar['settings'] = json_decode(base64_decode($params['settings']));
    }
} else {
    $mpar = array('id' => $params['id'], 'module' => $params['module']);
}

if (isset($params['custom-class'])) {
    $data_live_edit .= ' data-custom-class="' . $params['custom-class'] . '"';
}

if ($mod_class != false) {

    if (!is_admin()) {
        $data_type = 'data-mw-live-edit-url="' . admin_url('view:module/settings#action=modules/load_admin_side:') . mw_url_encode($params['id']) . '"';
    } else {
        $data_type = 'data-mw-live-edit-url="' . admin_url('view:module/settings#action=modules/load_admin_side:') . mw_url_encode($params['id']) . '"';
    }

} else {
    $mod_class = 'custom/' . $params['type'];
    if (isset($config->live_edit[$mod_class])) {
        if (!is_admin()) {
            $data_type = " data-mw-live-edit-url='" . admin_url('view:module/settings#action=custom/' . urlencode($params['type']) . ':' . mw_url_encode($params['id'])) . "'";
        } else {
            $data_type = " data-mw-live-edit-url='" . admin_url('view:module/settings#action=custom/' . urlencode($params['type']) . ':' . mw_url_encode($params['id'])) . "'";
        }
    } else {

        $data_type = "";

    }
}

?>
<div class="mw-live-edit" data-field="module-<?php print $params['id']; ?>" <?php print $data_type; ?> <?php print $data_live_edit; ?>>{content}</div>