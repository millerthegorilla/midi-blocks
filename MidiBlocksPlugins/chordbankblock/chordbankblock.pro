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

target.path = /usr/local/share/MidiBlocks/plugins
INSTALLS += target

