QMAKE_CXX = ccache g++

TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = beatdividerblock.h \
                ../interfacedef/controlblockinterface.h
SOURCES       = beatdividerblock.cpp
FORMS         = beatdividerblockeditor.ui
TARGET        = $$qtLibraryTarget(beatdividerblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$$$shadowed($$PWD)/$$PLUGIN_PATH
     !exists($$INSTALL_PATH) { system( mkdir -p $$INSTALL_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

DISTFILES += \
    ./beatdividerblock.includes
