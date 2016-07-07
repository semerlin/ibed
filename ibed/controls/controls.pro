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
    mainwidget.cpp \
    baseinfowidget.cpp \
    bednumwidget.cpp \
    patientinfowidget.cpp \
    patientadvisewidget.cpp \
    advisewidget.cpp \
    adviseinfowidget.cpp

HEADERS += controls.h\
        controls_global.h \
    maintopwidget.h \
    mainbottomwidget.h \
    mainwidget.h \
    baseinfowidget.h \
    bednumwidget.h \
    patientinfowidget.h \
    patientadvisewidget.h \
    advisewidget.h \
    adviseinfowidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    maintopwidget.ui \
    mainbottomwidget.ui \
    mainwidget.ui \
    baseinfowidget.ui \
    bednumwidget.ui \
    patientinfowidget.ui \
    patientadvisewidget.ui \
    advisewidget.ui

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/basecontrols/ -lbasecontrols

INCLUDEPATH += $$PWD/../corelib/basecontrols
DEPENDPATH += $$PWD/../corelib/basecontrols

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/utility/ -lutility

INCLUDEPATH += $$PWD/../corelib/utility
DEPENDPATH += $$PWD/../corelib/utility
