TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = beatdividerblock.h controlblock.h
SOURCES       = beatdividerblock.cpp
FORMS         = beatdividerblockeditor.ui
TARGET        = $$qtLibraryTarget(beatdividerblockplugin)

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target

