
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

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$top_builddir/$$PLUGIN_PATH
     !exists($$PLUGIN_PATH) { system( mkdir -p $$PLUGIN_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target
