######################################################################
# Automatically generated by qmake (1.03a) Fri Aug 23 15:01:33 2002
######################################################################

TEMPLATE = lib
CONFIG -= moc
CONFIG += plugin thread
target.path = /usr/local/lib/mythtv/filters
INSTALLS = target

INCLUDEPATH += ../../libs/libNuppelVideo

QMAKE_CFLAGS_RELEASE += -Wno-missing-prototypes
QMAKE_CFLAGS_DEBUG += -Wno-missing-prototypes

# Input
HEADERS += mmx.h
SOURCES += filter_linearblend.c
