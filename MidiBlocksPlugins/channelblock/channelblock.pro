TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = channelblock.h controlblock.h
SOURCES       = channelblock.cpp
FORMS         = channelblockeditor.ui
TARGET        = $$qtLibraryTarget(channelblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$top_builddir/$$PLUGIN_PATH
     !exists($$PLUGIN_PATH) { system( mkdir -p $$PLUGIN_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

