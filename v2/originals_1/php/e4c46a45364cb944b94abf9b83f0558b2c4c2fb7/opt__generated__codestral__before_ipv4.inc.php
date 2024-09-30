<script>
// ...
post: function () {
    return {
        id: "address-search",
        search_type: "ipv4",
        device_id: '<?php echo json_encode($_POST['device_id'], JSON_HEX_TAG); ?>',
        interface: '<?php echo json_encode($_POST['interface'], JSON_HEX_TAG); ?>',
        address: '<?php echo json_encode($_POST['address'], JSON_HEX_TAG); ?>'
    };
},
// ...
formatters: {
    "tooltip": function (column, row) {
            var value = row[column.id];
            var encodedValue = $('<div/>').text(value).html(); // Encoding using jQuery text method to encode HTML special characters
            return "<span title='" + encodedValue + "' data-toggle='tooltip'>" + encodedValue + "</span>";
        },
},
// ...
</script>
