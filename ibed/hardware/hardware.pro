#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T15:31:06
#
#-------------------------------------------------

QT       -= gui

TARGET = hardware
TEMPLATE = lib

DEFINES += HARDWARE_LIBRARY

SOURCES += hardware.cpp

HEADERS += hardware.h\
        hardware_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
