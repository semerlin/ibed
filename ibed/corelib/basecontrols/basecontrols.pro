#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T15:10:11
#
#-------------------------------------------------

QT      += gui

TARGET = basecontrols
TEMPLATE = lib

DEFINES += BASECONTROLS_LIBRARY

SOURCES += basecontrols.cpp \
    basebuttonbox.cpp

HEADERS += basecontrols.h\
        basecontrols_global.h \
    basebuttonbox.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    basebuttonbox.ui
