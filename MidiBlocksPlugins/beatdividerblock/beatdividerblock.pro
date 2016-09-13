TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = beatdividerblock.h controlblock.h
SOURCES       = beatdividerblock.cpp
FORMS         = beatdividerblockeditor.ui
TARGET        = $$qtLibraryTarget(beatdividerblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$top_builddir/$$PLUGIN_PATH
     !exists($$PLUGIN_PATH) { system( mkdir -p $$PLUGIN_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

