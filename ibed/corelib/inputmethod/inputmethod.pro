#-------------------------------------------------
#
# Project created by QtCreator 2016-08-09T20:10:26
#
#-------------------------------------------------

QT       += gui

TARGET = inputmethod
TEMPLATE = lib

include (../../global.pri)

DEFINES += INPUTMETHOD_LIBRARY

SOURCES += inputmethod.cpp \
    numipmethod.cpp \
    numpanel.cpp

HEADERS += inputmethod.h\
        inputmethod_global.h \
    numipmethod.h \
    numpanel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    numpanel.ui

DISTFILES +=
