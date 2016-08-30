#-------------------------------------------------
#
# Project created by QtCreator 2016-04-06T21:29:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = excutable
TEMPLATE = app

include(../alsa.pri)

SOURCES += main.cpp

HEADERS  +=

FORMS    +=

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/hardware/ -lhardware

INCLUDEPATH += $$PWD/../corelib/hardware
DEPENDPATH += $$PWD/../corelib/hardware


unix:!macx: LIBS += -L$$OUT_PWD/../corelib/utility/ -lutility

INCLUDEPATH += $$PWD/../corelib/utility
DEPENDPATH += $$PWD/../corelib/utility

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/framework/ -lframework

INCLUDEPATH += $$PWD/../corelib/framework
DEPENDPATH += $$PWD/../corelib/framework

unix:!macx: LIBS += -L$$OUT_PWD/../modules/ -lmodules

INCLUDEPATH += $$PWD/../modules
DEPENDPATH += $$PWD/../modules

unix:!macx: LIBS += -L$$OUT_PWD/../3rdpart/log4qt/ -llog4qt

INCLUDEPATH += $$PWD/../3rdpart/log4qt
DEPENDPATH += $$PWD/../3rdpart/log4qt

unix:!macx: LIBS += -L$$OUT_PWD/../commonunit/ -lcommonunit

INCLUDEPATH += $$PWD/../commonunit
DEPENDPATH += $$PWD/../commonunit

unix:!macx: LIBS += -L$$OUT_PWD/../mainmodule/ -lmainmodule

INCLUDEPATH += $$PWD/../mainmodule
DEPENDPATH += $$PWD/../mainmodule

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
