 
[PYTHON]
def process_common_params(data):
    # data is a dictionary of POST parameters
    for key in data:
        if key == "token":
            continue
        if len(key) > 2 and key[:2] == "__":
            continue
        yield (key, data[key])
[/PYTHON]
