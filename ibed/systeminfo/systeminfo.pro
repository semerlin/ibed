#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T14:04:49
#
#-------------------------------------------------

QT       -= gui

TARGET = systeminfo
TEMPLATE = lib

DEFINES += SYSTEMINFO_LIBRARY

SOURCES += systeminfo.cpp \
    memory.cpp \
    cpu.cpp \
    time.cpp

HEADERS += systeminfo.h\
        systeminfo_global.h \
    memory.h \
    cpu.h \
    time.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
