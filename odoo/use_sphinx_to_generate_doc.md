# Install sphinx & use

http://www.sphinx-doc.org/en/1.4/install.html

# setup conf.py

```python
# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# http://www.sphinx-doc.org/en/master/config

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))
# -*- coding: utf-8 -*-
import sys, os
import sphinx

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
DIR = os.path.dirname(__file__)

# autodoc
sys.path.append(os.path.abspath(os.path.join(DIR, '../odoo12')))


# -- Project information -----------------------------------------------------

project = 'odoo12'
copyright = '2019, telesoho'
author = 'telesoho'

language = 'ja'
latex_docclass = {'manual': 'jsbook'}


# The full version, including alpha/beta/rc tags
release = '12.0'

# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx.ext.autodoc'
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'alabaster'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

```

# How to generate Japanese or Chinese PDF by sphinx

```sh
sudo apt-get install texlive texlive-lang-all texlive-latex-extra
make latexpdfja
```
