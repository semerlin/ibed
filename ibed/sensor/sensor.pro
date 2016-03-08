#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T14:45:07
#
#-------------------------------------------------

QT       -= gui

TARGET = sensor
TEMPLATE = lib

DEFINES += SENSOR_LIBRARY

SOURCES += sensor.cpp \
    iserialport.cpp \
    posix_serialport.cpp

HEADERS += sensor.h\
        sensor_global.h \
    iserialport.h \
    posix_serialport.h \
    serialdef.h \
    serialportctrl.h \
    win_serialport.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
