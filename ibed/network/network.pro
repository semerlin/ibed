#-------------------------------------------------
#
# Project created by QtCreator 2016-08-04T21:41:00
#
#-------------------------------------------------

QT       += network

TARGET = network
TEMPLATE = lib

include(../global.pri)

DEFINES += NETWORK_LIBRARY

SOURCES += network.cpp \
    basedatahandler.cpp \
    defaultclient.cpp \
    netprotocol.cpp \
    registerdatahandler.cpp \
    baseinfodatahandler.cpp \
    heartbeatdatahandler.cpp \
    advisedatahandler.cpp \
    defaultdataprocess.cpp \
    docadvisedatahandler.cpp \
    bedcontroldatahandler.cpp

HEADERS += network.h\
        network_global.h \
    basedatahandler.h \
    defaultclient.h \
    idatahandler.h \
    netprotocol.h \
    registerdatahandler.h \
    baseinfodatahandler.h \
    heartbeatdatahandler.h \
    advisedatahandler.h \
    defaultdataprocess.h \
    docadvisedatahandler.h \
    bedcontroldatahandler.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../commonunit/ -lcommonunit

INCLUDEPATH += $$PWD/../commonunit
DEPENDPATH += $$PWD/../commonunit

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/utility/ -lutility

INCLUDEPATH += $$PWD/../corelib/utility
DEPENDPATH += $$PWD/../corelib/utility

unix:!macx: LIBS += -L$$OUT_PWD/../3rdpart/log4qt/ -llog4qt

INCLUDEPATH += $$PWD/../3rdpart/log4qt
DEPENDPATH += $$PWD/../3rdpart/log4qt
