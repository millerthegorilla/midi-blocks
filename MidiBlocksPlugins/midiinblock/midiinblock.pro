QMAKE_CXX = ccache g++

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
HEADERS       = midiinblock.h \
                ../interfacedef/controlblockinterface.h \
                RtMidi.h \
                RtError.h
SOURCES       = midiinblock.cpp \
    RtMidi.cpp
FORMS         = midiinblockeditor.ui
TARGET        = $$qtLibraryTarget(midiinblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$top_builddir/$$PLUGIN_PATH
     !exists($$INSTALL_PATH) { system( mkdir -p $$INSTALL_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

DISTFILES += \
    ../MidiBlockPlugins.includes
