#-------------------------------------------------
#
# Project created by QtCreator 2016-04-17T20:48:03
#
#-------------------------------------------------

QT       += widgets

TARGET = controls
TEMPLATE = lib

DEFINES += CONTROLS_LIBRARY

SOURCES += controls.cpp \
    maintopwidget.cpp \
    mainbottomwidget.cpp

HEADERS += controls.h\
        controls_global.h \
    maintopwidget.h \
    mainbottomwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    maintopwidget.ui \
    mainbottomwidget.ui
