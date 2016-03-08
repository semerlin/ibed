#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T16:02:33
#
#-------------------------------------------------

QT       -= gui

TARGET = patient
TEMPLATE = lib

DEFINES += PATIENT_LIBRARY

SOURCES += patient.cpp

HEADERS += patient.h\
        patient_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
