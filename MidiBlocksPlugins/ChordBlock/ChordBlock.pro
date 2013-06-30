TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = chordblock.h controlblock.h
SOURCES       = chordblock.cpp
FORMS         = chordblockeditor.ui
TARGET        = $$qtLibraryTarget(chordblockplugin)

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target

