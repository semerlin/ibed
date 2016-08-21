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
    lightintensity.cpp \
    bedcontrol.cpp \
    bedctrlprotocol.cpp \
    sht20.cpp \
    i2cdevice.cpp

HEADERS += sensor.h\
        sensor_global.h \
    lightintensity.h \
    bedcontrol.h \
    bedctrlprotocol.h \
    sht20.h \
    i2cdevice.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/hardware/ -lhardware

INCLUDEPATH += $$PWD/../corelib/hardware
DEPENDPATH += $$PWD/../corelib/hardware

unix:!macx: LIBS += -L$$OUT_PWD/../commonunit/ -lcommonunit

INCLUDEPATH += $$PWD/../commonunit
DEPENDPATH += $$PWD/../commonunit

unix:!macx: LIBS += -L$$OUT_PWD/../3rdpart/log4qt/ -llog4qt

INCLUDEPATH += $$PWD/../3rdpart/log4qt
DEPENDPATH += $$PWD/../3rdpart/log4qt
