#-------------------------------------------------
#
# Project created by QtCreator 2016-04-23T17:04:42
#
#-------------------------------------------------

QT       += gui

TARGET = framework
TEMPLATE = lib

include(../../boost.pri)

DEFINES += FRAMEWORK_LIBRARY

SOURCES += framework.cpp \
    simplestatemachine.cpp \
    baseappmodule.cpp \
    modulemanger.cpp \
    baseapplaunch.cpp

HEADERS += framework.h\
        framework_global.h \
    simplestatemachine.h \
    iappmodule.h \
    baseappmodule.h \
    modulemanger.h \
    baseapplaunch.h \
    iapplaunch.h \
    iapplaunchwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../../3rdpart/log4qt/ -llog4qt

INCLUDEPATH += $$PWD/../../3rdpart/log4qt
DEPENDPATH += $$PWD/../../3rdpart/log4qt

FORMS +=
