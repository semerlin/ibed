#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T14:04:35
#
#-------------------------------------------------

QT       -= gui

TARGET = netprotocol
TEMPLATE = lib

DEFINES += NETPROTOCOL_LIBRARY

SOURCES += netprotocol.cpp

HEADERS += netprotocol.h\
        netprotocol_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
