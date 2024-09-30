 
[PYTHON]
def check_storage_support(type):
    try:
        window[type].setItem('PMATest', 'test')
        # Check whether key-value pair was set successfully
        if window[type].getItem('PMATest') == 'test':
            # Supported, remove test variable from storage
            window[type].removeItem('PMATest')
            return True
    except:
        # Not supported
        print("Your browser does not support web storage.")
    return False

def ignore_php_errors(clear_prev_errors):
    if clear_prev_errors == None or clear_prev_errors is False:
        str = False
    # send AJAX request to error_report.php with send_error_report=0, exception_type=php & token.
    # It clears the prev_errors stored in session.
    if clear_prev_errors:
        pass
    # remove displayed errors
    pma_errors = $('#pma_errors')
    pma_errors.fadeOut("slow")
    pma_errors.remove()

def handle_keydown(e):
    if (e.ctrlKey and e.which == 13) or (e.altKey and e.which == 13):
        form = $(this).closest('form')
        if not form.find('input[type="submit"]') or not form.find('input[type="submit"]').click():
            form.submit()

$(document).on('keydown', 'form input, form textarea, form select', handle_keydown)

# Display warning regarding SSL when sha256_password
# method is selected
# Used in user_password.php (Change Password link on index.php)
$(document).on("change", "select#select_authentication_plugin_cp", function():
    if this.value == 'sha256_password':
        $('#ssl_reqd_warning_cp').show()
    else:
        $('#ssl_reqd_warning_cp').hide()
)
[/PYTHON]
