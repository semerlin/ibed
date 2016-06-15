#-------------------------------------------------
#
# Project created by QtCreator 2016-06-15T20:12:46
#
#-------------------------------------------------

QT       -= gui

TARGET = resource
TEMPLATE = lib

DEFINES += RESOURCE_LIBRARY

SOURCES +=

HEADERS +=

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    res.qrc
