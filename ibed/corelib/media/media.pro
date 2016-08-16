#-------------------------------------------------
#
# Project created by QtCreator 2016-08-12T22:34:09
#
#-------------------------------------------------

QT       += gui


TARGET = media
TEMPLATE = lib

include(../../alsa.pri)

DEFINES += MEDIA_LIBRARY

SOURCES += media.cpp \
    AudioPlay.cpp \
    AudioRecord.cpp \
    audioformat.cpp \
    audiodeviceinfo.cpp \
    audiointensity.cpp

HEADERS += media.h\
        media_global.h \
    AudioPlay.h \
    AudioRecord.h \
    audioformat.h \
    audiodeviceinfo.h \
    audio.h \
    audiointensity.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}



unix:!macx: LIBS += -L$$OUT_PWD/../../3rdpart/log4qt/ -llog4qt

INCLUDEPATH += $$PWD/../../3rdpart/log4qt
DEPENDPATH += $$PWD/../../3rdpart/log4qt

unix:!macx: LIBS += -L$$OUT_PWD/../utility/ -lutility

INCLUDEPATH += $$PWD/../utility
DEPENDPATH += $$PWD/../utility
