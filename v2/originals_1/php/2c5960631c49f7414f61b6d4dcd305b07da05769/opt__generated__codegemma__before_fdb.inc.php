```php
<script>

var grid = $("#fdb-search").bootgrid({
    ajax: true,
    rowCount: [50, 100, 250, -1],
    templates: {
        header: "<div id=\"{{ctx.id}}\" class=\"{{css.header}}\"><div class=\"row\">"+
                "<div class=\"col-sm-9 actionBar\"><span class=\"pull-left\">"+
                "<form method=\"post\" action=\"\" class=\"form-inline\" role=\"form\">"+
                "<?php echo htmlspecialchars(csrf_field()) ?>"+
                "<div class=\"form-group\">"+
                "<select name=\"device_id\" id=\"device_id\" class=\"form-control input-sm\">"+
                "<option value=\"\">All Devices</option>"+
<?php

// Select the devices only with FDB tables
$sql = 'SELECT D.device_id AS device_id, `hostname`, `sysName`, `display` FROM `ports_fdb` AS F, `ports` AS P, `devices` AS D';
$param = [];

if (! Auth::user()->hasGlobalRead()) {
    $device_ids = Permissions::devicesForUser()->toArray() ?: [0];
    $where .= ' AND `D`.`device_id` IN ' . dbGenPlaceholders(count($device_ids));
    $param = $device_ids;
}

$result = DB::select($sql, $param);

foreach ($result as $row) {
    echo "<option value=\"" . $row['device_id'] . "\">" . $row['hostname'] . "</option>";
}
?>

                "</select>"+
                "</div>"+
                "<div class=\"form-group\">"+
                "<input type=\"text\" name=\"searchby\" id=\"searchby\" class=\"form-control input-sm\">"+
                "<option value=\"mac\" "+
<?php
if ($vars['searchby'] == 'mac') {
    echo '" selected "+';
}
?>

                ">MAC Address</option>"+
                "<option value=\"ip\" "+
<?php
if ($vars['searchby'] == 'ip') {
    echo '" selected "+';
}
?>

                ">IP Address</option>"+
                "<option value=\"dnsname\" "+
<?php
if ($vars['searchby'] == 'dnsname') {
    echo '" selected "+';
}
?>

                ">DNS Name</option>"+
                "<option value=\"description\" "+
<?php
if ($vars['searchby'] == 'description') {
    echo '" selected "+';
}
?>

                ">Description</option>"+
                "<option value=\"vendor\" "+
<?php
if ($vars['searchby'] == 'vendor') {
    echo '" selected "+';
}
?>

                ">Vendor</option>"+
                "<option value=\"vlan\" "+
<?php
if ($vars['searchby'] == 'vlan') {
    echo '" selected "+';
}
?>

                ">Vlan</option>"+
                "</select>"+
                "</div>"+
                "<div class=\"form-group\">"+
                "<input type=\"text\" name=\"searchPhrase\" id=\"address\" value=\""+
<?php
echo '"' . $vars['searchPhrase'] . '"+';
?>

                "\" class=\"form-control input-sm\" placeholder=\"Value\" />"+
                "</div>"+
                "<button type=\"submit\" class=\"btn btn-default input-sm\">Search</button>"+
                "</form></span></div>"+
               "<div class=\"col-sm-3 actionBar\"><p class=\"{{css.actions}}\"></p></div></div></div>"
    },
    post: function ()
    {
        return {
            device_id: '<?php echo htmlspecialchars($vars['device_id']); ?>',
            searchby: '<?php echo htmlspecialchars($vars['searchby']); ?>',
            searchPhrase: '<?php echo htmlspecialchars($vars['searchPhrase']); ?>',
            dns: $("#fdb-search").bootgrid("getColumnSettings").find(col => col.id === "dnsname").visible,
        };
    },
    url: "<?php echo url('/ajax/table/fdb-tables'); ?>",
    formatters: {
        "tooltip": function (column, row) {
                var value = row[column.id];
                var vendor = '';
                if (column.id == 'mac_address' && ((vendor = row['mac_oui']) != '' )) {
                    return "<span title=\'" + value + " (" + vendor + ")\' data-toggle=\'tooltip\'>" + value + "</span>";
                }
                return "<span title=\'" + value + "\' data-toggle=\'tooltip\'>" + value + "</span>";
            },
    },
});

</script>
