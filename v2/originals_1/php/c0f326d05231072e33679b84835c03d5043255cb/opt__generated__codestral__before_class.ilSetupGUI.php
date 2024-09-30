 <script>
    function toggleProxyStatus() {
        var proxyStatus = document.getElementById('proxy_status');
        var proxyAvailability = document.getElementById('proxy_availability');

        if (proxyStatus.checked) {
            proxyAvailability.style.display = 'block';
        } else {
            proxyAvailability.style.display = 'none';
        }
    }
</script>
<?php