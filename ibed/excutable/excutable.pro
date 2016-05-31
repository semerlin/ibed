#-------------------------------------------------
#
# Project created by QtCreator 2016-04-06T21:29:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = excutable
TEMPLATE = app


SOURCES += main.cpp \
    lanchwidget.cpp

HEADERS  += \
    lanchwidget.h

FORMS    += \
    lanchwidget.ui

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/hardware/ -lhardware

INCLUDEPATH += $$PWD/../corelib/hardware
DEPENDPATH += $$PWD/../corelib/hardware

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/hardware/ -lhardware

INCLUDEPATH += $$PWD/../corelib/hardware
DEPENDPATH += $$PWD/../corelib/hardware

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/utility/ -lutility

INCLUDEPATH += $$PWD/../corelib/utility
DEPENDPATH += $$PWD/../corelib/utility

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/framework/ -lframework

INCLUDEPATH += $$PWD/../corelib/framework
DEPENDPATH += $$PWD/../corelib/framework

RESOURCES += \
    resource.qrc
