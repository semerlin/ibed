#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T21:30:37
#
#-------------------------------------------------

QT       += gui

TARGET = commonunit
TEMPLATE = lib

DEFINES += COMMONUNIT_LIBRARY

SOURCES += commonunit.cpp \
    applogger.cpp \
    appsetting.cpp \
    appuiconfig.cpp

HEADERS += commonunit.h\
        commonunit_global.h \
    applogger.h \
    appsetting.h \
    appuiconfig.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../3rdpart/log4qt/ -llog4qt

INCLUDEPATH += $$PWD/../3rdpart/log4qt
DEPENDPATH += $$PWD/../3rdpart/log4qt

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/utility/ -lutility

INCLUDEPATH += $$PWD/../corelib/utility
DEPENDPATH += $$PWD/../corelib/utility
