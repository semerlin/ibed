#-------------------------------------------------
#
# Project created by QtCreator 2016-04-17T20:48:03
#
#-------------------------------------------------

QT       += widgets

TARGET = controls
TEMPLATE = lib

include(../global.pri)
include(../boost.pri)

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
    adviseinfowidget.cpp \
    inoutwidget.cpp \
    inouteditlabellistdelegate.cpp \
    educationwidget.cpp \
    settingwidget.cpp \
    localethwidget.cpp \
    serverethwidget.cpp \
    screenwidget.cpp \
    soundwidget.cpp \
    infusionwidget.cpp \
    bedwidget.cpp \
    standbywidget.cpp \
    progressdialog.cpp \
    callwidget.cpp

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
    adviseinfowidget.h \
    inoutwidget.h \
    inouteditlabellistdelegate.h \
    educationwidget.h \
    settingwidget.h \
    localethwidget.h \
    serverethwidget.h \
    screenwidget.h \
    soundwidget.h \
    infusionwidget.h \
    bedwidget.h \
    standbywidget.h \
    calldialog.h \
    progressdialog.h \
    callwidget.h

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
    advisewidget.ui \
    inoutwidget.ui \
    educationwidget.ui \
    settingwidget.ui \
    localethwidget.ui \
    serverethwidget.ui \
    screenwidget.ui \
    soundwidget.ui \
    infusionwidget.ui \
    bedwidget.ui \
    standbywidget.ui \
    progressdialog.ui \
    callwidget.ui

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/basecontrols/ -lbasecontrols

INCLUDEPATH += $$PWD/../corelib/basecontrols
DEPENDPATH += $$PWD/../corelib/basecontrols

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/utility/ -lutility

INCLUDEPATH += $$PWD/../corelib/utility
DEPENDPATH += $$PWD/../corelib/utility

unix:!macx: LIBS += -L$$OUT_PWD/../commonunit/ -lcommonunit

INCLUDEPATH += $$PWD/../commonunit
DEPENDPATH += $$PWD/../commonunit
