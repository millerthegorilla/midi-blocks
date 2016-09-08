
win32 {
LIBS += -lwinmm
QMAKE_CXXFLAGS = -D__WINDOWS_MM__
}

unix {
LIBS += -lasound -lpthread
QMAKE_CXXFLAGS = -D__LINUX_ALSA__
}

TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = midioutblock.h \
    RtMidi.h \
    RtError.h \
    controlblock.h
SOURCES       = midioutblock.cpp \
    RtMidi.cpp
FORMS         = midioutblockeditor.ui
TARGET        = $$qtLibraryTarget(midioutblockplugin)

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target

