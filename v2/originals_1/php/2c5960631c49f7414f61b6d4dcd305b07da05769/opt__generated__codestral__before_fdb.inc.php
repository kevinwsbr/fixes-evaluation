<script>
...
    post: function () {
        return {
            device_id: <?php echo json_encode($vars['device_id']); ?>,
            searchby: <?php echo json_encode($vars['searchby']); ?>,
            searchPhrase: <?php echo json_encode($vars['searchPhrase']); ?>,
            dns: $("#fdb-search").bootgrid("getColumnSettings").find(col => col.id === "dnsname").visible,
        };
    },
...
</script>
