#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T22:20:13
#
#-------------------------------------------------

QT       -= gui

TARGET = modules
TEMPLATE = lib

DEFINES += MODULES_LIBRARY

SOURCES += modules.cpp \
    hardwaremodule.cpp

HEADERS += modules.h\
        modules_global.h \
    hardwaremodule.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../corelib/framework/release/ -lframework
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../corelib/framework/debug/ -lframework
else:unix: LIBS += -L$$OUT_PWD/../corelib/framework/ -lframework

INCLUDEPATH += $$PWD/../corelib/framework
DEPENDPATH += $$PWD/../corelib/framework


unix:!macx: LIBS += -L$$OUT_PWD/../corelib/hardware/ -lhardware

INCLUDEPATH += $$PWD/../corelib/hardware
DEPENDPATH += $$PWD/../corelib/hardware
