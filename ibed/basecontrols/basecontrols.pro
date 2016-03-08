#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T15:43:19
#
#-------------------------------------------------

QT       -= gui

TARGET = basecontrols
TEMPLATE = lib

DEFINES += BASECONTROLS_LIBRARY

SOURCES += basecontrols.cpp \
    backlight.cpp \
    volume.cpp \
    network.cpp

HEADERS += basecontrols.h\
        basecontrols_global.h \
    backlight.h \
    volume.h \
    network.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
