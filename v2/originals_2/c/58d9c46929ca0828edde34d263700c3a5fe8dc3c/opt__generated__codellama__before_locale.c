
[PYTHON]
import os
from typing import Any, Dict, List, Union

class Locale:
    def __init__(self):
        self.encoding = "UTF-8"
        self.language = ""
        self.territory = ""
        self.codeset = ""
        self.modifiers = []

    def __repr__(self) -> str:
        return f"{self.language}-{self.territory}.{self.codeset} {','.join(self.modifiers)}"

    def parse_locale_string(self, locale_string: str) -> None:
        self.language = locale_string.split(".")[0]
        self.territory = "-".join(locale_string.split("-")[1:])
        self.codeset = ""
        self.modifiers = []

    def get_lang_and_country(self) -> List[str]:
        return [self.language, self.territory]

def locale_from_string(locale_string: str) -> Locale:
    locale = Locale()
    locale.parse_locale_string(locale_string)
    return locale

def get_available_locales() -> List[str]:
    locales = os.listdir("/usr/share/i18n/locales")
    locales = [x.split(".")[0] for x in locales if x.endswith(".dat")]
    return locales

def get_preferred_locale() -> str:
    locale = os.getenv("LANG")
    if not locale:
        raise ValueError("LANG environment variable is not set")
    return locale
[/PYTHON]
