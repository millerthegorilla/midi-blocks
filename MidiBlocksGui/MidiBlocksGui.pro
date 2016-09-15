#-------------------------------------------------
#
# Project created by QtCreator 2013-06-30T13:06:23
#
#-------------------------------------------------
QMAKE_CXX = ccache g++

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
    ../MidiBlocksPlugins/interfacedef/controlblockinterface.h \
    controlblockgraphicsitem.h \
    connection.h \
    controlgraphicsscene.h \
    pluginlistmodel.h

FORMS    += mainwindow.ui

INSTALL_PATH = "usr/local/bin"
PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"


CONFIG(debug, debug|release) {
     INSTALL_PATH = $$shadowed($$PWD)/../$$INSTALL_PATH
     PLUGIN_PATH = $$shadowed($$PWD)/../$$PLUGIN_PATH
     !exists($$INSTALL_PATH) { system( mkdir -p $$INSTALL_PATH ) }
     !exists($$PLUGIN_PATH) { system( mkdir -p $$PLUGIN_PATH ) }
}

DEFINES += "INSTALL_PATH=\\\"$$INSTALL_PATH\\\""
DEFINES += "PLUG_PATH=\\\"$$PLUGIN_PATH\\\""

target.path = $$INSTALL_PATH

INSTALLS += target

DISTFILES += \
    ./midiblocksgui.includes
