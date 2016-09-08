TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = metronomeblock.h controlblock.h
SOURCES       = metronomeblock.cpp
FORMS         = metronomeblockeditor.ui
TARGET        = $$qtLibraryTarget(metronomeblockplugin)

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target

