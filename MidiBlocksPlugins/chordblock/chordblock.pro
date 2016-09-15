QMAKE_CXX = ccache g++
QT += widgets
TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = chordblock.h \
                ../interfacedef/controlblockinterface.h
SOURCES       = chordblock.cpp
FORMS         = chordblockeditor.ui
TARGET        = $$qtLibraryTarget(chordblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$shadowed($$PWD)/../../$$PLUGIN_PATH
     !exists($$INSTALL_PATH) { system( mkdir -p $$INSTALL_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

DISTFILES += \
    ./chordblock.includes
