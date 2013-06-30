TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = transposeblock.h controlblock.h
SOURCES       = transposeblock.cpp
FORMS         = transposeblockeditor.ui
TARGET        = $$qtLibraryTarget(transposeblockplugin)

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target

