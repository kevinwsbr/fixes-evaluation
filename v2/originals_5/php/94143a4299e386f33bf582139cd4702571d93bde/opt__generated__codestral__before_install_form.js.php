   function testftp(form){
       postDataReturnText('installer.php','-action=testftp&...'+escape(form.ftp_host.value)+'&...', ...);
   }

   function testdb(form){
       postDataReturnText('installer.php','-action=testdb&...'+escape(form.database_name.options[form.database_name.selectedIndex].value)+'&...', ...);
   }

   var listeners = {
      'database_name' : {
          'onchange' : function(fld){
              // ... vulnerable code here as it modifies HTML directly with user input
          }
       },
      'install_type': {
           'onchange': function(fld){
               // ... another potentially vulnerable code section
           }
      }
   };
   