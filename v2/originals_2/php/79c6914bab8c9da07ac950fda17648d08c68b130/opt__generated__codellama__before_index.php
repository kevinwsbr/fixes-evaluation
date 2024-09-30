 
[PYTHON]
def get_module_settings(id, params):
    module_settings = {}
    if id and params:
        for key in params:
            if key.startswith('module_settings['):
                setting_name = key[len('module_settings['):-1]
                module_settings[setting_name] = params[key]
    return module_settings


def get_live_edit_data(id, params):
    live_edit_data = {}
    if id and params:
        for key in params:
            if key.startswith('live_edit['):
                setting_name = key[len('live_edit['):-1]
                live_edit_data[setting_name] = params[key]
    return live_edit_data


def get_style_settings(id, params):
    style_settings = {}
    if id and params:
        for key in params:
            if key.startswith('style['):
                setting_name = key[len('style['):-1]
                style_settings[setting_name] = params[key]
    return style_settings


def get_advanced_settings(id, params):
    advanced_settings = {}
    if id and params:
        for key in params:
            if key.startswith('advanced['):
                setting_name = key[len('advanced['):-1]
                advanced_settings[setting_name] = params[key]
    return advanced_settings


def get_template_settings(id, params):
    template_settings = {}
    if id and params:
        for key in params:
            if key.startswith('template['):
                setting_name = key[len('template['):-1]
                template_settings[setting_name] = params[key]
    return template_settings


def get_all_settings(id, params):
    all_settings = {}
    if id and params:
        for key in params:
            if key.startswith('module_settings[') or key.startswith('live_edit[') or key.startswith('style[') or key.startswith('advanced[') or key.startswith('template['):
                all_settings[key] = params[key]
    return all_settings
[/PYTHON]
