#-------------------------------------------------
#
# Project created by QtCreator 2016-04-06T21:29:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = excutable
TEMPLATE = app


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

RESOURCES += \
    ../resource/res.qrc

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
