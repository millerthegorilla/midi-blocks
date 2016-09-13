#-------------------------------------------------
#
# Project created by QtCreator 2013-06-30T13:06:23
#
#-------------------------------------------------

QT       += core gui widgets

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

INSTALL_PATH = "usr/local/bin"
PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$top_builddir/$$INSTALL_PATH
     PLUGIN_PATH = $$top_builddir/$$PLUGIN_PATH
     !exists($$INSTALL_PATH) { system( mkdir -p $$INSTALL_PATH ) }
     !exists($$PLUGIN_PATH) { system( mkdir -p $$PLUGIN_PATH ) }
}

DEFINES += "INSTALL_PATH=\\\"$$INSTALL_PATH\\\""
DEFINES += "PLUG_PATH=\\\"$$PLUGIN_PATH\\\""

target.path = $$INSTALL_PATH

INSTALLS += target
