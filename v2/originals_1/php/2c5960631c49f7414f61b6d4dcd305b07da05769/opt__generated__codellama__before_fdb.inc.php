<div class="panel panel-default panel-condensed">
    <div class="panel-heading">FDB Tables</div>
    <div class="panel-body">
        <script type="text/javascript">
            $('#fdb-tables').bootgrid({
                ajax: true,
                url: "<?php echo url('/ajax/table/fdb-tables'); ?>",
                post: function () {
                    return {
                        device_id: '<?php echo htmlspecialchars($vars['device_id']); ?>',
                        searchby: '<?php echo addslashes(htmlspecialchars($vars['searchby'])); ?>',
                        searchPhrase: '<?php echo addslashes(htmlspecialchars($vars['searchPhrase'])); ?>',
                        dns: $("#fdb-tables").bootgrid("getColumnSettings").find(col => col.id === "dnsname").visible,
                    };
                },
                templates: {
                    header: '<div id="{{ctx.id}}" class="{{css.header}}"><div class="row">' +
                        '<div class="col-xs-6"><p class="{{css.search}}"></p></div>' +
                        '<div class="col-xs-6"><p class="{{css.actions}}"></p></div>' +
                    '</div></div>',
                    search: function (ctx) {
                        var column = ctx.column;
                        var searchby = $('#searchby').val();
                        var searchPhrase = $('#address').val();
                        if (!column || !searchby || !searchPhrase) {
                            return '';
                        }
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
    </div>
</div>
