#-------------------------------------------------
#
# Project created by QtCreator 2013-06-30T13:06:23
#
#-------------------------------------------------

QT       += core gui

TARGET = midi-blocks
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controlblockgraphicsitem.cpp \
    connection.cpp \
    controlgraphicsscene.cpp \
    pluginlistmodel.cpp

HEADERS  += mainwindow.h \
    controlblock.h \
    controlblockgraphicsitem.h \
    connection.h \
    controlgraphicsscene.h \
    pluginlistmodel.h

FORMS    += mainwindow.ui

target.path = /usr/local/bin/
INSTALLS += target
