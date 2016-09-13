

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

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$top_builddir/$$PLUGIN_PATH
     !exists($$PLUGIN_PATH) { system( mkdir -p $$PLUGIN_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target




