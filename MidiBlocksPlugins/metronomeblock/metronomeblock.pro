QMAKE_CXX = ccache g++

TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = metronomeblock.h \
                ../interfacedef/controlblockinterface.h
SOURCES       = metronomeblock.cpp
FORMS         = metronomeblockeditor.ui
TARGET        = $$qtLibraryTarget(metronomeblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$top_builddir/$$PLUGIN_PATH
     !exists($$INSTALL_PATH) { system( mkdir -p $$INSTALL_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

DISTFILES += \
    ../MidiBlockPlugins.includes
