#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T15:10:11
#
#-------------------------------------------------

QT      += gui

TARGET = basecontrols
TEMPLATE = lib

DEFINES += BASECONTROLS_LIBRARY

SOURCES += basecontrols.cpp \
    basebuttonbox.cpp \
    iconbuttonbox.cpp \
    basewidget.cpp \
    iconpushbutton.cpp \
    linetableview.cpp \
    labellineedit.cpp \
    editlabellistitem.cpp \
    editlabellistdelegate.cpp \
    editlabellistmodel.cpp \
    editlabellistview.cpp \
    musicplaylistitem.cpp \
    musicplaylistview.cpp \
    musicplaylistmodel.cpp \
    musicplaylistdelegate.cpp \
    labelslider.cpp \
    circleprogressbar.cpp \
    dotlabel.cpp \
    baselabel.cpp \
    pixmaplabel.cpp \
    basedialog.cpp \
    clickablelabel.cpp

HEADERS += basecontrols.h\
        basecontrols_global.h \
    basebuttonbox.h \
    iconbuttonbox.h \
    basewidget.h \
    iconpushbutton.h \
    linetableview.h \
    labellineedit.h \
    editlabellistitem.h \
    editlabellistdelegate.h \
    editlabellistmodel.h \
    editlabellistview.h \
    musicplaylistitem.h \
    musicplaylistview.h \
    musicplaylistmodel.h \
    musicplaylistdelegate.h \
    labelslider.h \
    circleprogressbar.h \
    dotlabel.h \
    baselabel.h \
    pixmaplabel.h \
    basedialog.h \
    clickablelabel.h \
    editlabellistview_p.h \
    editlabellistitem_p.h \
    musicplaylistitem_p.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    basebuttonbox.ui \
    labellineedit.ui \
    labelslider.ui \
    dotlabel.ui \
    pixmaplabel.ui

unix:!macx: LIBS += -L$$OUT_PWD/../utility/ -lutility

INCLUDEPATH += $$PWD/../utility
DEPENDPATH += $$PWD/../utility
