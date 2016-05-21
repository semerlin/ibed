#-------------------------------------------------
#
# Project created by QtCreator 2016-04-23T17:04:42
#
#-------------------------------------------------

QT       += gui

TARGET = framework
TEMPLATE = lib

DEFINES += FRAMEWORK_LIBRARY

SOURCES += framework.cpp \
    iapplancher.cpp \
    baseapplancher.cpp \
    simplestatemachine.cpp

HEADERS += framework.h\
        framework_global.h \
    iapplancher.h \
    baseapplancher.h \
    simplestatemachine.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../../3rdpart/log4qt/ -llog4qt

INCLUDEPATH += $$PWD/../../3rdpart/log4qt
DEPENDPATH += $$PWD/../../3rdpart/log4qt
