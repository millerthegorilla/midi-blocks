QMAKE_CXX = ccache g++

TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = transposeblock.h \
                ../interfacedef/controlblockinterface.h
SOURCES       = transposeblock.cpp
FORMS         = transposeblockeditor.ui
TARGET        = $$qtLibraryTarget(transposeblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$shadowed($$PWD)/../../$$PLUGIN_PATH
     !exists($$INSTALL_PATH) { system( mkdir -p $$INSTALL_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

DISTFILES += \
    ./transposeblock.includes
