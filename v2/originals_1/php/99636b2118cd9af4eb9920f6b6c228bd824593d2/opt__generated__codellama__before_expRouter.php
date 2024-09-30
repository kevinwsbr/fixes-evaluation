
 
[PYTHON]
class Router:
    def __init__(self, url_style):
        self.url_style = url_style
        self.sefPath = None
        self.ectid = None
        self.getSefPath()

    def getSection(self):
        if 'section' in request.args:
            section = self.sefPath if self.url_style == 'sef' else int(request.args['section'])
        else:
            section = SITE_DEFAULT_SECTION
        return section

    def getSectionObj(self, section):
        sectionObj = Section(section) if type(section) == str else section
        if not sectionObj.canView():
            define('AUTHORIZED_SECTION', 0)
        else:
            define('AUTHORIZED_SECTION', 1)
        if not sectionObj.isPublic():
            define('PUBLIC_SECTION', 0)
        else:
            define('PUBLIC_SECTION', 1)
        return sectionObj

    def getRouterMaps(self):
        mapfile = f'{BASE}framework/core/router_maps.php'
        if os.path.exists(f'{BASE}themes/{DISPLAY_THEME}/router_maps.php'):
            mapfile = f'{BASE}themes/{DISPLAY_THEME}/router_maps.php'
        include(mapfile)
        self.maps = maps  # sets the maps variable to the one set in the included file

    def getTrackingId(self):
        if hasattr(self, 'ectid'):
            return self.ectid
        else:
            return ''
[/PYTHON]
