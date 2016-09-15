QMAKE_CXX = ccache g++

QT += widgets

#this currently only works in linux with JACK
#TODO: make it work with windows
TEMPLATE      = lib
CONFIG        += plugin

HEADERS       = audiotomidiblock.h \
                ../interfacedef/controlblockinterface.h \
                chordprocessing.h
SOURCES       = audiotomidiblock.cpp \
                chordprocessing.cpp
FORMS         = audiotomidiblockeditor.ui
TARGET        = $$qtLibraryTarget(audiotomidiblockplugin)

PLUGIN_PATH = "usr/local/share/MidiBlocks/plugins"

CONFIG(debug, debug|release) {
     INSTALL_PATH = $$$$shadowed($$PWD)/$$PLUGIN_PATH
     !exists($$INSTALL_PATH) { system( mkdir -p $$INSTALL_PATH ) }
}
message($$system(ls $$PWD/../../))
target.path = $$INSTALL_PATH

INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../CLAM-1.4.0/scons/libs/core/release/ -llibclam_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../CLAM-1.4.0/scons/libs/core/debug/ -lclam_core
else:unix: LIBS += -L$$PWD/../../CLAM-1.4.0/scons/libs/core/ -lclam_core

INCLUDEPATH += $$PWD/../../CLAM-1.4.0/scons/libs/core/include/
DEPENDPATH += $$PWD/../../CLAM-1.4.0/scons/libs/core
HEADERS += $$PWD/../../CLAM-1.4.0/scons/libs/core/include/CLAM/*.hxx
#SOURCES += $$PWD/../CLAM-1.4.0/scons/libs/core/src/*.cxx

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../CLAM-1.4.0/scons/libs/processing/release/ -llibclam_processing
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../CLAM-1.4.0/scons/libs/processing/debug/ -llibclam_processing
else:unix: LIBS += -L$$PWD/../../CLAM-1.4.0/scons/libs/processing/ -lclam_processing

INCLUDEPATH += $$PWD/../../CLAM-1.4.0/scons/libs/processing/include/
DEPENDPATH += $$PWD/../../CLAM-1.4.0/scons/libs/processing
HEADERS += $$PWD/../../CLAM-1.4.0/scons/libs/processing/include/CLAM/*.hxx
#SOURCES += $$PWD/../CLAM-1.4.0/scons/libs/processing/src/*.cxx

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../CLAM-1.4.0/scons/libs/audioio/release/ -llibclam_audioio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../CLAM-1.4.0/scons/libs/audioio/debug/ -llibclam_audioio
else:unix: LIBS += -L$$PWD/../../CLAM-1.4.0/scons/libs/audioio/ -lclam_audioio

INCLUDEPATH += $$PWD/../../CLAM-1.4.0/scons/libs/audioio/include/
DEPENDPATH += $$PWD/../../CLAM-1.4.0/scons/libs/audioio
HEADERS += $$PWD/../../CLAM-1.4.0/scons/libs/audioio/include/CLAM/*.hxx
#SOURCES += $$PWD/../CLAM-1.4.0/scons/libs/audioio/src/*.cxx

DISTFILES += \
    ./audiotomidiblock.includes
