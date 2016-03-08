#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T15:48:29
#
#-------------------------------------------------

QT       -= gui

TARGET = hardware
TEMPLATE = lib

DEFINES += HARDWARE_LIBRARY

SOURCES += hardware.cpp \
    callbutton.cpp

HEADERS += hardware.h\
        hardware_global.h \
    callbutton.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
