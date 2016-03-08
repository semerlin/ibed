#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T14:01:17
#
#-------------------------------------------------

QT       -= gui

TARGET = log4qt
TEMPLATE = lib

DEFINES += LOG4QT_LIBRARY

SOURCES += log4qt.cpp

HEADERS += log4qt.h\
        log4qt_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
