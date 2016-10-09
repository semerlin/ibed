#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T20:46:39
#
#-------------------------------------------------

QT       -= gui

TARGET = call
TEMPLATE = lib

include(../global.pri)
include(../sip.pri)


DEFINES += CALL_LIBRARY

SOURCES += \
    callbtn.cpp \
    callmange.cpp \
    sip.cpp

HEADERS += call.h\
        call_global.h \
    callbtn.h \
    calldef.h \
    callmange.h \
    sip.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../commonunit/ -lcommonunit

INCLUDEPATH += $$PWD/../commonunit
DEPENDPATH += $$PWD/../commonunit

unix:!macx: LIBS += -L$$OUT_PWD/../3rdpart/log4qt/ -llog4qt

INCLUDEPATH += $$PWD/../3rdpart/log4qt
DEPENDPATH += $$PWD/../3rdpart/log4qt


unix:!macx: LIBS += -L$$OUT_PWD/../corelib/utility/ -lutility

INCLUDEPATH += $$PWD/../corelib/utility
DEPENDPATH += $$PWD/../corelib/utility

unix:!macx: LIBS += -L$$OUT_PWD/../commonunit/ -lcommonunit

INCLUDEPATH += $$PWD/../commonunit
DEPENDPATH += $$PWD/../commonunit
