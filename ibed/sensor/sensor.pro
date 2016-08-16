#-------------------------------------------------
#
# Project created by QtCreator 2016-04-11T20:52:27
#
#-------------------------------------------------

QT       -= gui

TARGET = sensor
TEMPLATE = lib

DEFINES += SENSOR_LIBRARY

SOURCES += sensor.cpp \
    lightintensity.cpp

HEADERS += sensor.h\
        sensor_global.h \
    lightintensity.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
