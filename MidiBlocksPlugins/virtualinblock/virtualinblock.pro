QMAKE_CXX = ccache g++

LIBS += -lasound -lpthread
QMAKE_CXXFLAGS = -D__LINUX_ALSA__

TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = virtualinblock.h \
                ../interfacedef/controlblockinterface.h \
                RtError.h \
                RtMidi.h
SOURCES       = virtualinblock.cpp \
                RtMidi.cpp
FORMS         = virtualinblockeditor.ui
TARGET        = $$qtLibraryTarget(virtualinblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$$$shadowed($$PWD)/$$PLUGIN_PATH
     !exists($$INSTALL_PATH) { system( mkdir -p $$INSTALL_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

DISTFILES += \
    ./virtualinblock.includes
