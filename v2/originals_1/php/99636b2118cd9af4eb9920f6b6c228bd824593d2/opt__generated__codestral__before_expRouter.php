import re

# Define the class and its methods
class expRouter:
    def __init__(self):
        # Initialize any necessary variables here
        self.sefPath = None
        self.ectid = None
        self.params = {}  # Assuming this is a dictionary for storing parameters

    def parseURL(self):
        if 'REQUEST_URI' in _SERVER:
            self.sefPath = urllib.parse.unquote(_SERVER['REQUEST_URI'])
        else:
            # Handle the case when 'REQUEST_URI' is not present in _SERVER
            pass

        self.sefPath = self.sefPath[len(PATH_RELATIVE) - 1:]
        if self.sefPath.startswith('/index.php'):
            self.sefPath = None

        if 'argv' in _SERVER and isinstance(_SERVER['argv'], list):
            for set in _SERVER['argv']:
                s = set.split("=")
                if s[0] == "ectid":
                    self.ectid = s[1]

        if self.sefPath and self.sefPath.endswith("/"):
            self.sefPath = self.sefPath[:-1]

        sefPath = re.split('">', self.sefPath)[0]
        self.sefPath = expString.escape(expString.sanitize(sefPath))

    def getSection(self):
        global db  # Assuming 'db' is a global variable

        if expTheme.inAction():
            if 'section' in _REQUEST:
                section = self.getPageByName(_REQUEST['section']).id if self.url_style == "sef" else int(_REQUEST['section'])
            else:
                section = expSession.get('last_section') if expSession.is_set('last_section') else SITE_DEFAULT_SECTION
        else:
            section = int(_REQUEST['section']) if 'section' in _REQUEST else SITE_DEFAULT_SECTION

        testsection = db.selectObject('section', f'id={section}')
        if not testsection:
            section = SITE_DEFAULT_SECTION

        return section

    def getSectionObj(self, section):
        global db  # Assuming 'db' is a global variable

        if section == "*":
            sectionObj = getattr(expModules.getModuleClassName(self.params['controller']), "getSection")(self.params)
        else:
            sectionObj = section(int(section))

        if not sectionObj.canView():
            AUTHORIZED_SECTION = 0
        else:
            AUTHORIZED_SECTION = 1

        if not sectionObj.isPublic():
            PUBLIC_SECTION = 0
        else:
            PUBLIC_SECTION = 1

        if 'section' in _REQUEST:
            expSession.set('last_section', int(_REQUEST['section']))
        elif section == SITE_DEFAULT_SECTION:
            expSession.set('last_section', int(SITE_DEFAULT_SECTION))
        else:
            # No need to unset the 'last_section' here as it was not set in the first place
            pass

        return sectionObj

    def getRouterMaps(self):
        mapfile = BASE + 'framework/core/router_maps.php'
        if os.path.exists(BASE + f'themes/{DISPLAY_THEME}/router_maps.php'):
            mapfile = BASE + f'themes/{DISPLAY_THEME}/router_maps.php'

        with open(mapfile, 'r') as file:
            code = compile(file.read(), mapfile, 'exec')
            exec(code)

        self.maps = maps  # Assuming 'maps' is defined in the executed code

    def getTrackingId(self):
        return self.ectid if self.ectid else ''
