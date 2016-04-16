#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T20:07:55
#
#-------------------------------------------------

QT       -= gui

TARGET = hardware
TEMPLATE = lib

DEFINES += HARDWARE_LIBRARY

SOURCES += hardware.cpp \
    backlight.cpp \
    iserialport.cpp \
    posix_serialport.cpp \
    powermange.cpp

HEADERS += hardware.h\
        hardware_global.h \
    backlight.h \
    iserialport.h \
    posix_serialport.h \
    serialdef.h \
    serialportctrl.h \
    win_serialport.h \
    powermange.h \
    ipowermangedevice.h \
    powerdef.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../utility/ -lutility

INCLUDEPATH += $$PWD/../utility
DEPENDPATH += $$PWD/../utility

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../utility/release/ -lutility
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../utility/debug/ -lutility
else:unix: LIBS += -L$$OUT_PWD/../utility/ -lutility

INCLUDEPATH += $$PWD/../utility
DEPENDPATH += $$PWD/../utility
