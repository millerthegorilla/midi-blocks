QT += widgets

#this currently only works in linux with JACK
#TODO: make it work with windows
TEMPLATE      = lib
CONFIG        += plugin

HEADERS       = audiotomidiblock.h controlblock.h \
    chordprocessing.h
SOURCES       = audiotomidiblock.cpp \
    chordprocessing.cpp
FORMS         = audiotomidiblockeditor.ui
TARGET        = $$qtLibraryTarget(audiotomidiblockplugin)

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target

LIBS += -lclam_core -lclam_audioio -lclam_processing
