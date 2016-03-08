#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T16:00:55
#
#-------------------------------------------------

QT       -= gui

TARGET = bedcontrol
TEMPLATE = lib

DEFINES += BEDCONTROL_LIBRARY

SOURCES += bedcontrol.cpp

HEADERS += bedcontrol.h\
        bedcontrol_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
