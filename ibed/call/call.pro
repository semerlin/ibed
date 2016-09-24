#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T20:46:39
#
#-------------------------------------------------

QT       -= gui

TARGET = call
TEMPLATE = lib

DEFINES += CALL_LIBRARY

SOURCES += call.cpp \
    callbtn.cpp \
    callin.cpp \
    callinconnectedstate.cpp \
    callinconnectingstate.cpp \
    callinlocalterminatestate.cpp \
    callinremoteterminatestate.cpp \
    callmange.cpp \
    callout.cpp \
    calloutconnectedstate.cpp \
    calloutconnectingstate.cpp \
    calloutlocalterminatestate.cpp \
    calloutremoteterminatestate.cpp \
    calltranstraction.cpp

HEADERS += call.h\
        call_global.h \
    callbtn.h \
    calldef.h \
    callevent.h \
    callin.h \
    callinconnectedstate.h \
    callinconnectingstate.h \
    callinlocalterminatestate.h \
    callinremoteterminatestate.h \
    callmange.h \
    callout.h \
    calloutconnectedstate.h \
    calloutconnectingstate.h \
    calloutlocalterminatestate.h \
    calloutremoteterminatestate.h \
    calltranstraction.h

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
