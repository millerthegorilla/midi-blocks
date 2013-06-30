
# virtual ins don't work on windows
unix {

LIBS += -lasound -lpthread
QMAKE_CXXFLAGS = -D__LINUX_ALSA__

TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = virtualinblock.h controlblock.h \
    RtError.h \
    RtMidi.h
SOURCES       = virtualinblock.cpp \
    RtMidi.cpp
FORMS         = virtualinblockeditor.ui
TARGET        = $$qtLibraryTarget(virtualinblockplugin)

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target
}




