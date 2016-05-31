#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T21:30:37
#
#-------------------------------------------------

QT       -= gui

TARGET = commonunit
TEMPLATE = lib

DEFINES += COMMONUNIT_LIBRARY

SOURCES += commonunit.cpp \
    applogger.cpp

HEADERS += commonunit.h\
        commonunit_global.h \
    applogger.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
