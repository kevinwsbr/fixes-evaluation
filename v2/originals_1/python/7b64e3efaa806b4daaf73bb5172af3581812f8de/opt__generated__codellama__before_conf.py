# -*- coding: utf-8 -*-
# fastecdsa documentation build configuration file, created by
# sphinx-quickstart on Thu Dec 15 20:02:52 2016.
#
# This file is execfile()d with the current directory set to its
# containing dir.
#
# Note that not all possible configuration values are present in this
# autogenerated file.
#
# All configuration values have a default; values that are commented out
# serve to show the default.

import os
import sys
from unittest import mock

MOCK_MODULES = ['fastecdsa._ecdsa', 'fastecdsa.curvemath']
for mod_name in MOCK_MODULES:
    sys.modules[mod_name] = mock.Mock()

extensions = ['sphinx.ext.mathjax', 'sphinx.ext.autodoc']
templates_path = ['_templates']
source_suffix = ['.rst', '.md']
master_doc = 'index'
project = 'fastecdsa'
copyright = '{}, Anton Kueltz'.format(datetime.now().year)
author = 'Anton Kueltz'
version = '2.1'
release = '2.1.1'
language = None
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']
pygments_style = 'sphinx'
todo_include_todos = False
html_theme = 'default'
html_static_path = ['_static']
latex_elements = {
    # The paper size ('letterpaper' or 'a4paper').
    #
    # 'papersize': 'letterpaper',

    # The font size ('10pt', '11pt' or '12pt').
    #
    # 'pointsize': '10pt',

    # Additional stuff for the LaTeX preamble.
    #
    # 'preamble': '',

    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',
}
latex_documents = [
    (master_doc, 'fastecdsa.tex', 'fastecdsa Documentation',
     'Anton Kueltz', 'manual'),
]
man_pages = [
    (master_doc, 'fastecdsa', 'fastecdsa Documentation',
     [author], 1)
]
texinfo_documents = [
    (master_doc, 'fastecdsa', 'fastecdsa Documentation',
     author, 'fastecdsa', 'One line description of project.',
     'Miscellaneous'),
]
