#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T14:07:13
#
#-------------------------------------------------

QT       -= gui

TARGET = autotest
TEMPLATE = lib

DEFINES += AUTOTEST_LIBRARY

SOURCES += autotest.cpp

HEADERS += autotest.h\
        autotest_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
