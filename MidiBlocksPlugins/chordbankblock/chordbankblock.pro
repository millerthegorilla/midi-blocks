QT            += widgets
TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = chordbankblock.h controlblock.h \
    chordbankmodel.h \
    chorditemdelegate.h \
    chordeditor.h
SOURCES       = chordbankblock.cpp \
    chordbankmodel.cpp \
    chorditemdelegate.cpp \
    chordeditor.cpp
FORMS         = chordbankblockeditor.ui \
    chordeditor.ui
TARGET        = $$qtLibraryTarget(chordbankblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$top_builddir/$$PLUGIN_PATH
     !exists($$PLUGIN_PATH) { system( mkdir -p $$PLUGIN_PATH ) }
}

target.path = $$INSTALL_PATH

INSTALLS += target

