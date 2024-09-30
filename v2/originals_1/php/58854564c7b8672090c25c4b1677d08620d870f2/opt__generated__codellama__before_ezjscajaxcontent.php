[PYTHON]
class Util:
    @staticmethod
    def to_xml(dictionary):
        root = etree.Element('root')
        for key, value in dictionary.items():
            if isinstance(value, dict):
                child = etree.SubElement(root, key)
                Util.to_xml(value, child)
            else:
                element = etree.SubElement(root, key)
                element.text = str(value)
        return etree.tostring(root, encoding='unicode', method='xml')

    @staticmethod
    def format_locale_date(timestamp, type):
        locale = eZLocale.instance()
        method = getattr(locale, f"getFormattingFunction", None)
        if method:
            formatted_date = getattr(locale, f"{type}")(timestamp)
        return formatted_date
[/PYTHON]
