QMAKE_CXX = ccache g++

TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = channelblock.h \
                ../interfacedef/controlblockinterface.h
SOURCES       = channelblock.cpp
FORMS         = channelblockeditor.ui
TARGET        = $$qtLibraryTarget(channelblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$top_builddir/$$PLUGIN_PATH
     !exists($$INSTALL_PATH) { system( mkdir -p $$INSTALL_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

DISTFILES += \
    ../MidiBlockPlugins.includes
