TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = metronomeblock.h controlblock.h
SOURCES       = metronomeblock.cpp
FORMS         = metronomeblockeditor.ui
TARGET        = $$qtLibraryTarget(metronomeblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$top_builddir/$$PLUGIN_PATH
     !exists($$PLUGIN_PATH) { system( mkdir -p $$PLUGIN_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

