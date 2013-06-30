TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = channelblock.h controlblock.h
SOURCES       = channelblock.cpp
FORMS         = channelblockeditor.ui
TARGET        = $$qtLibraryTarget(channelblockplugin)

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target

