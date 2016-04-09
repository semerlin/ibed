#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T15:30:43
#
#-------------------------------------------------

QT       -= gui

TARGET = systeminfo
TEMPLATE = lib

DEFINES += SYSTEMINFO_LIBRARY

SOURCES += systeminfo.cpp

HEADERS += systeminfo.h\
        systeminfo_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
