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
    mainbottomwidget.cpp \
    mainwidget.cpp

HEADERS += controls.h\
        controls_global.h \
    maintopwidget.h \
    mainbottomwidget.h \
    mainwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    maintopwidget.ui \
    mainbottomwidget.ui \
    mainwidget.ui
