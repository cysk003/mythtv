# -*- coding: UTF-8 -*-

# ----------------------
# Name: comedycentral_api - XPath and XSLT functions for the Comedy Central RSS/HTML items
# Python Script
# Author:   R.D. Vaughan
# Purpose:  This python script is intended to perform a variety of utility functions
#           for the conversion of data to the MNV standard RSS output format.
#           See this link for the specifications:
#           http://www.mythtv.org/wiki/MythNetvision_Grabber_Script_Format
#
# License:Creative Commons GNU GPL v2
# (http://creativecommons.org/licenses/GPL/2.0/)
#-------------------------------------
__title__ ="comedycentral_api - XPath and XSLT functions for the Comedy Central RSS/HTML"
__author__="R.D. Vaughan"
__purpose__='''
This python script is intended to perform a variety of utility functions
for the conversion of data to the MNV standard RSS output format.
See this link for the specifications:
http://www.mythtv.org/wiki/MythNetvision_Grabber_Script_Format
'''

__version__="v0.1.0"
# 0.1.0 Initial development


# Specify the class names that have XPath extention functions
__xpathClassList__ = ['xpathFunctions', ]

# Specify the XSLT extention class names. Each class is a stand lone extention function
#__xsltExtentionList__ = ['xsltExtExample', ]
__xsltExtentionList__ = []

import os, sys, re, time, datetime, shutil, urllib.request, urllib.parse, urllib.error, string
from copy import deepcopy
import io

class OutStreamEncoder(object):
    """Wraps a stream with an encoder"""
    def __init__(self, outstream, encoding=None):
        self.out = outstream
        if not encoding:
            self.encoding = sys.getfilesystemencoding()
        else:
            self.encoding = encoding

    def write(self, obj):
        """Wraps the output stream, encoding Unicode strings with the specified encoding"""
        if isinstance(obj, str):
            obj = obj.encode(self.encoding)
        try:
            self.out.buffer.write(obj)
        except OSError:
            pass

    def __getattr__(self, attr):
        """Delegate everything but write to the stream"""
        return getattr(self.out, attr)

if isinstance(sys.stdout, io.TextIOWrapper):
    sys.stdout = OutStreamEncoder(sys.stdout, 'utf8')
    sys.stderr = OutStreamEncoder(sys.stderr, 'utf8')

try:
    from io import StringIO
    from lxml import etree
except Exception as e:
    sys.stderr.write('\n! Error - Importing the "lxml" and "StringIO" python libraries failed on error(%s)\n' % e)
    sys.exit(1)


class xpathFunctions(object):
    """Functions specific extending XPath
    """
    def __init__(self):
        self.functList = ['comedycentralMakeLink', ]
        self.persistence = {}
    # end __init__()

######################################################################################################
#
# Start of XPath extension functions
#
######################################################################################################

    def comedycentralMakeLink(self, context, *arg):
        '''Parse the item element and extract a Web link
        Call example: 'mnvXpath:comedycentralMakeLink(.)'
        return a URL link to the item web page
        '''
        tmpTitle = arg[0][0].find('title').text.strip()
        tmpVideoCode = arg[0][0].find('guid').text.strip()
        index = tmpVideoCode.rfind('.')
        if index != -1:
            tmpVideoCode = tmpVideoCode[index+1:]
        tmpLink = common.linkWebPage('dummy', 'comedycentral').replace('TITLE', urllib.parse.quote(tmpTitle)).replace('VIDEOCODE', tmpVideoCode)
        return tmpLink.strip()
    # end comedycentralMakeLink()

######################################################################################################
#
# End of XPath extension functions
#
######################################################################################################

######################################################################################################
#
# Start of XSLT extension functions
#
######################################################################################################

######################################################################################################
#
# End of XSLT extension functions
#
######################################################################################################
