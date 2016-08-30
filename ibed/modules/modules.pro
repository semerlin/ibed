#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T22:20:13
#
#-------------------------------------------------

QT       += gui
QT       += network

TARGET = modules
TEMPLATE = lib

include(../global.pri)
include(../alsa.pri)

DEFINES += MODULES_LIBRARY

SOURCES += modules.cpp \
    hardwaremodule.cpp \
    thememodule.cpp \
    uimodule.cpp \
    networkmodule.cpp \
    mediamodule.cpp \
    callmodule.cpp

HEADERS += modules.h\
        modules_global.h \
    hardwaremodule.h \
    thememodule.h \
    uimodule.h \
    networkmodule.h \
    mediamodule.h \
    callmodule.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../corelib/framework/release/ -lframework
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../corelib/framework/debug/ -lframework
else:unix: LIBS += -L$$OUT_PWD/../corelib/framework/ -lframework

INCLUDEPATH += $$PWD/../corelib/framework
DEPENDPATH += $$PWD/../corelib/framework


unix:!macx: LIBS += -L$$OUT_PWD/../corelib/hardware/ -lhardware

INCLUDEPATH += $$PWD/../corelib/hardware
DEPENDPATH += $$PWD/../corelib/hardware

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/utility/ -lutility

INCLUDEPATH += $$PWD/../corelib/utility
DEPENDPATH += $$PWD/../corelib/utility

unix:!macx: LIBS += -L$$OUT_PWD/../commonunit/ -lcommonunit

INCLUDEPATH += $$PWD/../commonunit
DEPENDPATH += $$PWD/../commonunit

unix:!macx: LIBS += -L$$OUT_PWD/../3rdpart/log4qt/ -llog4qt

INCLUDEPATH += $$PWD/../3rdpart/log4qt
DEPENDPATH += $$PWD/../3rdpart/log4qt

unix:!macx: LIBS += -L$$OUT_PWD/../controls/ -lcontrols

INCLUDEPATH += $$PWD/../controls
DEPENDPATH += $$PWD/../controls

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/basecontrols/ -lbasecontrols

INCLUDEPATH += $$PWD/../corelib/basecontrols
DEPENDPATH += $$PWD/../corelib/basecontrols

unix:!macx: LIBS += -L$$OUT_PWD/../network/ -lnetwork

INCLUDEPATH += $$PWD/../network
DEPENDPATH += $$PWD/../network

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/inputmethod/ -linputmethod

INCLUDEPATH += $$PWD/../corelib/inputmethod
DEPENDPATH += $$PWD/../corelib/inputmethod

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/media/ -lmedia

INCLUDEPATH += $$PWD/../corelib/media
DEPENDPATH += $$PWD/../corelib/media

unix:!macx: LIBS += -L$$OUT_PWD/../sensor/ -lsensor

INCLUDEPATH += $$PWD/../sensor
DEPENDPATH += $$PWD/../sensor

unix:!macx: LIBS += -L$$OUT_PWD/../call/ -lcall

INCLUDEPATH += $$PWD/../call
DEPENDPATH += $$PWD/../call
