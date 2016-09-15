QMAKE_CXX = ccache g++

TEMPLATE = subdirs

SUBDIRS =  \
        arpeggiatorblock\
        beatdividerblock\
        beattoggleblock\
        channelblock\
        chordbankblock\
        chordblock\
        metronomeblock\
        midiinblock\
        midioutblock\
        splitterblock\
        transposeblock

unix {
SUBDIRS += \
        audiotomidiblock \
        virtualinblock
}



