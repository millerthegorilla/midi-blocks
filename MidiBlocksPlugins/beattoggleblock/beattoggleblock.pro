TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = beattoggleblock.h controlblock.h
SOURCES       = beattoggleblock.cpp
FORMS         = beattoggleblockeditor.ui
TARGET        = $$qtLibraryTarget(beattoggleblockplugin)

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target

