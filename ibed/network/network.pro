#-------------------------------------------------
#
# Project created by QtCreator 2016-08-04T21:41:00
#
#-------------------------------------------------

QT       += network

TARGET = network
TEMPLATE = lib

DEFINES += NETWORK_LIBRARY

SOURCES += network.cpp \
    basedatahandler.cpp \
    defaultclient.cpp \
    netprotocol.cpp \
    registerdatahandler.cpp \
    servermanger.cpp \
    baseinfodatahandler.cpp \
    heartbeatdatahandler.cpp \
    advisedatahandler.cpp

HEADERS += network.h\
        network_global.h \
    basedatahandler.h \
    defaultclient.h \
    idatahandler.h \
    netprotocol.h \
    registerdatahandler.h \
    baseinfodatahandler.h \
    heartbeatdatahandler.h \
    advisedatahandler.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../commonunit/ -lcommonunit

INCLUDEPATH += $$PWD/../commonunit
DEPENDPATH += $$PWD/../commonunit
