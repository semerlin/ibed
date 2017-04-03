#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T15:11:12
#
#-------------------------------------------------

QT      += gui

TARGET = utility
TEMPLATE = lib

DEFINES += UTILITY_LIBRARY

SOURCES += utility.cpp \
    qssloader.cpp \
    systemcall.cpp \
    util.cpp \
    formula.cpp \
    crc.cpp \
    bitops.cpp

HEADERS += utility.h\
        utility_global.h \
    qssloader.h \
    systemcall.h \
    util.h \
    formula.h \
    coveragecircularqueue.h \
    crc.h \
    bitops.h \
    funcwrap.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
