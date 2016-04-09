#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T15:11:12
#
#-------------------------------------------------

QT       -= gui

TARGET = utility
TEMPLATE = lib

DEFINES += UTILITY_LIBRARY

SOURCES += utility.cpp \
    qssloader.cpp

HEADERS += utility.h\
        utility_global.h \
    qssloader.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
