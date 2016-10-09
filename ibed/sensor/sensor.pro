#-------------------------------------------------
#
# Project created by QtCreator 2016-04-11T20:52:27
#
#-------------------------------------------------

QT       -= gui

TARGET = sensor
TEMPLATE = lib

include(../global.pri)
include(../boost.pri)

DEFINES += SENSOR_LIBRARY

SOURCES += sensor.cpp \
    lightintensity.cpp \
    bedcontrol.cpp \
    sht20.cpp \
    modbus.cpp \
    basedatahandler.cpp \
    weightdatahandler.cpp \
    keyboard.cpp \
    keyboardmange.cpp \
    kbdbacklight.cpp \
    infucountdatahandler.cpp \
    infuspeeddatahandler.cpp \
    infumountdatahandler.cpp \
    beddataprocess.cpp \
    beddatasend.cpp

HEADERS += sensor.h\
        sensor_global.h \
    lightintensity.h \
    bedcontrol.h \
    sht20.h \
    modbus.h \
    basedatahandler.h \
    bedcontrol.cpp.autosave \
    idatahandler.h \
    weightdatahandler.h \
    keyboard.h \
    keyboardmange.h \
    kbdbacklight.h \
    infucountdatahandler.h \
    infuspeeddatahandler.h \
    infumountdatahandler.h \
    beddataprocess.h \
    beddatasend.h

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

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/utility/ -lutility

INCLUDEPATH += $$PWD/../corelib/utility
DEPENDPATH += $$PWD/../corelib/utility
