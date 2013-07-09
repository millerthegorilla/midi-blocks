TEMPLATE = subdirs

SUBDIRS = \
        ArpeggiatorBlock\
        BeatDividerBlock\
        BeatToggleBlock\
        ChannelBlock\
        ChordBankBlock\
        ChordBlock\
        MetronomeBlock\
        MidiInBlock\
        MidiOutBlock\
        SplitterBlock\
        TransposeBlock

unix {
SUBDIRS += \
        AudioToMidiBlock \
        VirtualInBlock
}
