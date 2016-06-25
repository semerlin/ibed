#-------------------------------------------------
#
# Project created by QtCreator 2016-06-16T17:49:05
#
#-------------------------------------------------

QT       += gui

TARGET = mainmodule
TEMPLATE = lib

DEFINES += MAINMODULE_LIBRARY

SOURCES += mainmodule.cpp \
    appentry.cpp \
    launchwidget.cpp

HEADERS += mainmodule.h\
        mainmodule_global.h \
    appentry.h \
    launchwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../modules/ -lmodules

INCLUDEPATH += $$PWD/../modules
DEPENDPATH += $$PWD/../modules

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../commonunit/release/ -lcommonunit
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../commonunit/debug/ -lcommonunit
else:unix: LIBS += -L$$OUT_PWD/../commonunit/ -lcommonunit

INCLUDEPATH += $$PWD/../commonunit
DEPENDPATH += $$PWD/../commonunit

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/framework/ -lframework

INCLUDEPATH += $$PWD/../corelib/framework
DEPENDPATH += $$PWD/../corelib/framework

FORMS += \
    launchwidget.ui

unix:!macx: LIBS += -L$$OUT_PWD/../3rdpart/log4qt/ -llog4qt

INCLUDEPATH += $$PWD/../3rdpart/log4qt
DEPENDPATH += $$PWD/../3rdpart/log4qt

unix:!macx: LIBS += -L$$OUT_PWD/../corelib/utility/ -lutility

INCLUDEPATH += $$PWD/../corelib/utility
DEPENDPATH += $$PWD/../corelib/utility

unix:!macx: LIBS += -L$$OUT_PWD/../controls/ -lcontrols

INCLUDEPATH += $$PWD/../controls
DEPENDPATH += $$PWD/../controls
