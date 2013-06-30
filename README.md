# MIDI Blocks

A GUI that lets you manipulate MIDI in fun ways!

## Setup

Building MIDI Blocks requires Qt.  One of the Linux plugins requires
CLAM, and JACK.  See 'Prerequisites' for information on getting each of these.

Once you have the prerequisites installed, you can build the 
MIDI Blocks program and all of its plugins by executing the following
commands in the top directory of the project:

    qmake
    make

You can then install the midi-blocks binary in /usr/local/bin
and the plugins in /usr/local/share/MidiBlocks with:

    make install

Before running midi-blocks on Linux (with the AudioToMidiBlock),
you should make sure that you are running the JACK audio server
with your desired settings.

### Prerequisites

If you don't have Qt, you can get it from Qt Project webpage:
<http://qt-project.org/downloads>

On a Debian-like distribution you can get CLAM and JACK like this:

    sudo apt-get install libclam-dev

More information about JACK and CLAM can be found on their websites:
<http://clam-project.org/index.html>
<http://jackaudio.org/>

## Adding New Blocks

Adding new blocks to MIDI Blocks is EASY!  A Qt Creator project wizard for
making new ControlBlock implementations is included in misc/controlblockpluginwizard -
if you copy the controlblockpluginwizard directory to /usr/share/qtcreator/templates/wizards
on linux, or "Qt directory"/qtcreator/share/templates/wizards on windows, then you will be
able to select "MIDI Blocks Control Block Plugin" when you make a new project in Qt Creator.

## Getting Help and Helping Out

Please get in touch if you want help, or if you want to contribute to MIDI Blocks.

## License

MIDI Blocks is licensed under the General Public License version 3 or later.  See `GPLv3`.

Some of the default MIDI Blocks plugins contain the RtMidi source code.
RtMidi is licensed under a modified MIT License that can be found in `MidiBlocksPlugins/MidiInBlock/RtMidi.h`.
