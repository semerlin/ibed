#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T15:10:11
#
#-------------------------------------------------

QT      += gui

TARGET = basecontrols
TEMPLATE = lib

DEFINES += BASECONTROLS_LIBRARY

SOURCES += basecontrols.cpp

HEADERS += basecontrols.h\
        basecontrols_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
