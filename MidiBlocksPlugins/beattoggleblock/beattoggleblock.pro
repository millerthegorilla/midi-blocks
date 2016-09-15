QMAKE_CXX = ccache g++

TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = beattoggleblock.h \
                ../interfacedef/controlblockinterface.h
SOURCES       = beattoggleblock.cpp
FORMS         = beattoggleblockeditor.ui
TARGET        = $$qtLibraryTarget(beattoggleblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$$$shadowed($$PWD)/$$PLUGIN_PATH
     !exists($$INSTALL_PATH) { system( mkdir -p $$INSTALL_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

DISTFILES += \
    ./beattoggleblock.includes
