# -*- coding: UTF-8 -*-

# ----------------------
# Name: skyAtNight_api - XPath and XSLT functions for the BBC Sky at Night magazine RSS/HTML items
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
__title__ ="skyAtNight_api - XPath and XSLT functions for the BBC Sky at Night magazine RSS/HTML"
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
        self.functList = ['skyAtNightTitleEp', ]
    # end __init__()

######################################################################################################
#
# Start of XPath extension functions
#
######################################################################################################

    def skyAtNightTitleEp(self, context, *arg):
        '''Parse the guid element and extract an episode number
        Call example: 'mnvXpath:skyAtNightTitleEp(string(guid))'
        return the a massaged title element and an episode element in an array
        '''
        searchText = 'BBC_SAN'
        title = arg[0]
        episodeNumber = title.replace(searchText, '').strip()
        try:
            episodeNumber = int(episodeNumber)
        except:
            episodeNumber = None

        mythtvNamespace = "http://www.mythtv.org/wiki/MythNetvision_Grabber_Script_Format"
        mythtv = "{%s}" % mythtvNamespace
        NSMAP = {'mythtv' : mythtvNamespace}
        elementTmp = etree.Element(mythtv + "mythtv", nsmap=NSMAP)
        if not episodeNumber is None:
            etree.SubElement(elementTmp, "title").text = "EP%02d" % episodeNumber
            etree.SubElement(elementTmp, mythtv + "episode").text = "%s" % episodeNumber
        else:
            etree.SubElement(elementTmp, "title").text = title
        return elementTmp
    # end skyAtNightTitleEp()

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
