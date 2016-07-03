#-------------------------------------------------
#
# Project created by QtCreator 2016-07-02T23:29:39
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
    res.qrc \
    launch.qrc
