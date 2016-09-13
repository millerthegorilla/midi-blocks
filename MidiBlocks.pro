TEMPLATE = subdirs

SUBDIRS += \
    MidiBlocksGui \
    MidiBlocksPlugins

#QMAKE_LFLAGS_DEBUG += /NODEFAULTLIB:CLAM
message ($$PWD)

