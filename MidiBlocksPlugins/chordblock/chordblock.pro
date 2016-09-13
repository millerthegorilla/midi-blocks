TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = chordblock.h controlblock.h
SOURCES       = chordblock.cpp
FORMS         = chordblockeditor.ui
TARGET        = $$qtLibraryTarget(chordblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$top_builddir/$$PLUGIN_PATH
     !exists($$PLUGIN_PATH) { system( mkdir -p $$PLUGIN_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

