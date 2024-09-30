function testftp(form){
	
	postDataReturnText('installer.php','-action=testftp&-ftphost='+encodeURIComponent(form.ftp_host.value)+'&-ftpuser='+encodeURIComponent(form.ftp_username.value)+'&-ftppass='+encodeURIComponent(form.ftp_password.value)+'&-ftppath='+encodeURIComponent(form.ftp_path.value), function(result){
		var resultDiv = document.getElementById('ftp-test-results');
		eval('var results = '+result+';');
		resultDiv.innerHTML = results.message;
		});
	

}

function testdb(form){
	postDataReturnText('installer.php','-action=testdb&-dbname='+encodeURIComponent(form.database_name.options[form.database_name.selectedIndex].value)+'&-dbuser='+encodeURIComponent(form.mysql_user.value)+'&-dbpass='+encodeURIComponent(form.mysql_password.value), function(result){
		var resultDiv = document.getElementById('db-test-results');
		eval('var results = '+result+';');
		resultDiv.innerHTML = results.message;
	});
}
