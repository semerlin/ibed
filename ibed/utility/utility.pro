#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T15:29:23
#
#-------------------------------------------------

QT       -= gui

TARGET = utility
TEMPLATE = lib

DEFINES += UTILITY_LIBRARY

SOURCES += utility.cpp

HEADERS += utility.h\
        utility_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
