TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = arpeggiatorblock.h controlblock.h
SOURCES       = arpeggiatorblock.cpp
FORMS         = arpeggiatorblockeditor.ui
TARGET        = $$qtLibraryTarget(arpeggiatorblockplugin)

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target

