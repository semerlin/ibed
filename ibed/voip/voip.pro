#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T10:58:40
#
#-------------------------------------------------

QT       -= gui

TARGET = voip
TEMPLATE = lib

DEFINES += VOIP_LIBRARY

SOURCES += voip.cpp

HEADERS += voip.h\
        voip_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
