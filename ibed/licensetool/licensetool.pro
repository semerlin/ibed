#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T14:06:17
#
#-------------------------------------------------

QT       -= gui

TARGET = licensetool
TEMPLATE = lib

DEFINES += LICENSETOOL_LIBRARY

SOURCES += licensetool.cpp

HEADERS += licensetool.h\
        licensetool_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
