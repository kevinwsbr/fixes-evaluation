filter = "Hello, %u!"
user = "John"

result_len = filter_result_len(filter, user, NULL) // result_len = 13
result_str = filter_printf(filter, user) // result_str = "Hello, John!"
