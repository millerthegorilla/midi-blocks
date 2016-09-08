TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = splitterblock.h controlblock.h
SOURCES       = splitterblock.cpp
FORMS         = splitterblockeditor.ui
TARGET        = $$qtLibraryTarget(splitterblockplugin)

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target

