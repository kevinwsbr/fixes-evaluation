<?php
header('Content-type: text/javascript');
?>

/*------------------------------------------------------------------------------
 * End redefinition of window.alert function
 *----------------------------------------------------------------------------*/

function fieldInfo(id){
    alert(info[id]);
}

function testftp(form){
    var host = document.getElementById('ftp_host').value;
    var user = document.getElementById('ftp_username').value;
    var pass = document.getElementById('ftp_password').value;
    
    postDataReturnText('installer.php', '-action=testftp&-ftphost=' + escape(host) + '&-ftpuser=' + escape(user) + '&-ftppass=' + escape(pass) + '&-ftppath=' + escape(form.ftp_path.value), function(result){
        var resultDiv = document.getElementById('ftp-test-results');
        var results = eval('{' + result + '}');
        resultDiv.innerHTML = results.message;
    });
}

function testdb(form){
    var dbName = form.database_name.options[form.database_name.selectedIndex].value;
    var dbUser = document.getElementById('mysql_user').value;
    var dbPass = document.getElementById('mysql_password').value;
    
    postDataReturnText('installer.php', '-action=testdb&-dbname=' + escape(dbName) + '&-dbuser=' + escape(dbUser) + '&-dbpass=' + escape(dbPass), function(result){
        var resultDiv = document.getElementById('db-test-results');
        var results = eval('{' + result + '}');
        resultDiv.innerHTML = results.message;
    });
}

var listeners = {
    'database_name': {
        'onchange': function(fld){
            var option = fld.options[fld.selectedIndex].value;
            if (option) {
                document.getElementById('step2').style.display = '';
            } else {
                document.getElementById('step2').style.display = 'none';
            }
        }
    },
    'install_type': {
        'onchange': function(fld){
            var option = fld.options[fld.selectedIndex].value;
            if (option == 'ftp_install') {
                document.getElementById('step4').style.display = '';
            } else {
                document.getElementById('step4').style.display = 'none';
                document.getElementById('submitstep').style.display = '';
            }
        }
    }
};
