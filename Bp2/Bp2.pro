#-------------------------------------------------
#
# Project created by QtCreator 2013-04-02T19:25:46
#
#-------------------------------------------------

QT       += core gui \
            phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bp2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openfile.cpp \
    playlist.cpp

HEADERS  += mainwindow.h \
    openfile.h \
    playlist.h

RESOURCES += \
    source.qrc
