#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T16:04:31
#
#-------------------------------------------------

QT       -= gui

TARGET = commonunit
TEMPLATE = lib

DEFINES += COMMONUNIT_LIBRARY

SOURCES += \
    cryptogram.cpp \
    crc32.cpp

HEADERS += commonunit.h\
        commonunit_global.h \
    cryptogram.h \
    crc32.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
