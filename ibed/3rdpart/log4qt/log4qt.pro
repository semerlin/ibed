#-------------------------------------------------
#
# Project created by QtCreator 2016-05-16T21:53:31
#
#-------------------------------------------------

QT       -= gui

TARGET = log4qt
TEMPLATE = lib

include(./log4qt/log4qt.pri)

DEFINES += LOG4QT_LIBRARY

SOURCES +=

HEADERS +=\
        log4qt_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
