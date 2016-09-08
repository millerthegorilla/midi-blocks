
win32 {
LIBS += -lwinmm
QMAKE_CXXFLAGS = -D__WINDOWS_MM__ -D__RTMIDI_DEBUG__
}

unix {
LIBS += -lasound -lpthread
QMAKE_CXXFLAGS = -D__LINUX_ALSA__
}

TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = midiinblock.h controlblock.h \
    RtMidi.h \
    RtError.h
SOURCES       = midiinblock.cpp \
    RtMidi.cpp
FORMS         = midiinblockeditor.ui
TARGET        = $$qtLibraryTarget(midiinblockplugin)

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target

