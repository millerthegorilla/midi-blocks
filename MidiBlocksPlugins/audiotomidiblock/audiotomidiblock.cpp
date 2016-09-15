/*
    Copyright (C) 2013  Adam Nash

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

  */

#include "audiotomidiblock.h"
#include "ui_audiotomidiblockeditor.h"

#include <CLAM/AudioManager.hxx>
#include <CLAM/AudioSource.hxx>
#include <CLAM/ProcessingFactory.hxx>
#include <CLAM/JACKNetworkPlayer.hxx>
#include <CLAM/TonalAnalysis.hxx>
#include <CLAM/Err.hxx>

#include <QDebug>

#include "chordprocessing.h"

AudioToMidiBlock::AudioToMidiBlock(QObject *parent) :
    editorUi(new Ui::AudioToMidiBlockEditor)
{
    // There is probably a better way to make sure that there is an audio manager...
    try
    {
        CLAM::AudioManager::Current();
    }
    catch (CLAM::Err)
    {
        static CLAM::AudioManager audioManager( 44100, 512 );
    }

    if (parent)
    {
        setParent(parent);
    }
    
    editor = new QWidget();
    editorUi->setupUi(editor);

    m_baseNoteMap.insert("C", 0);
    m_baseNoteMap.insert("C#", 1);
    m_baseNoteMap.insert("Db", 1);
    m_baseNoteMap.insert("D", 2);
    m_baseNoteMap.insert("D#", 3);
    m_baseNoteMap.insert("Eb", 3);
    m_baseNoteMap.insert("E", 4);
    m_baseNoteMap.insert("F", 5);
    m_baseNoteMap.insert("F#", 6);
    m_baseNoteMap.insert("Gb", 6);
    m_baseNoteMap.insert("G", 7);
    m_baseNoteMap.insert("G#", 8);
    m_baseNoteMap.insert("Ab", 8);
    m_baseNoteMap.insert("A", 9);
    m_baseNoteMap.insert("A#", 10);
    m_baseNoteMap.insert("Bb", 10);
    m_baseNoteMap.insert("B", 11);

    QList<char> majorTriad;
    majorTriad.push_back(0);
    majorTriad.push_back(4);
    majorTriad.push_back(7);
    QList<char> dominant7 ;
    dominant7.push_back(0);
    dominant7.push_back(4);
    dominant7.push_back(7);
    dominant7.push_back(10);
    QList<char> major7 ;
    major7.push_back(0);
    major7.push_back(4);
    major7.push_back(7);
    major7.push_back(11);
    QList<char> minorTriad ;
    minorTriad.push_back(0);
    minorTriad.push_back(3);
    minorTriad.push_back(7);
    QList<char> minor6 ;
    minor6.push_back(0);
    minor6.push_back(3);
    minor6.push_back(7);
    minor6.push_back(8);
    QList<char> minor7 ;
    minor7.push_back(0);
    minor7.push_back(3);
    minor7.push_back(7);
    minor7.push_back(10);
    QList<char> minor7flat5 ;
    minor7flat5.push_back(0);
    minor7flat5.push_back(3);
    minor7flat5.push_back(6);
    minor7flat5.push_back(10);
    QList<char> dimTriad ;
    dimTriad.push_back(0);
    dimTriad.push_back(3);
    dimTriad.push_back(6);
    QList<char> powerChord ;
    powerChord.push_back(0);
    powerChord.push_back(7);
    QList<char> augmented ;
    augmented.push_back(0);
    augmented.push_back(4);
    augmented.push_back(8);

    m_chordNoteMap.insert("Major", majorTriad);
    m_chordNoteMap.insert("Dominant7", dominant7);
    m_chordNoteMap.insert("MajorMajor7", major7);
    m_chordNoteMap.insert("Major7", major7);
    m_chordNoteMap.insert("Minor", minorTriad);
    m_chordNoteMap.insert("Minor6", minor6);
    m_chordNoteMap.insert("Minor7", minor7);
    m_chordNoteMap.insert("Minor7-5", minor7flat5);
    m_chordNoteMap.insert("Diminished", dimTriad);
    m_chordNoteMap.insert("Power", powerChord);
    m_chordNoteMap.insert("Augmented", augmented);

    m_network.SetName("My Network");

    AudioSource* source = new AudioSource();
    TonalAnalysis* tAnalysis = new TonalAnalysis();
    ChordProcessing* chordProc = new ChordProcessing();

    connect(chordProc, SIGNAL(chordChanged(QString)),
            this, SLOT(setChord(QString)));
    connect(chordProc, SIGNAL(apparentNotes(QByteArray)),
            this, SLOT(setNotes(QByteArray)));

    connect(editorUi->doubleSpinBox, SIGNAL(valueChanged(double)),
            chordProc, SLOT(setThreshold(double)));
    chordProc->setThreshold(editorUi->doubleSpinBox->value());

    m_network.AddProcessing( "Audio In", source );
    m_network.AddProcessing( "Analysis", tAnalysis );
    m_network.AddProcessing( "Chord Processing", chordProc );

    m_network.ConnectPorts( "Audio In.1", "Analysis.Audio Input" );
    m_network.ConnectPorts( "Analysis.Chord Segmentation", "Chord Processing.Chord Segmentation" );
    m_network.ConnectPorts( "Analysis.Pitch Profile", "Chord Processing.Pitch Profile" );

    m_network.SetPlayer(new CLAM::JACKNetworkPlayer );

    m_network.Start();
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QAudioToMidiBlock")
}

AudioToMidiBlock::~AudioToMidiBlock()
{
    delete editorUi;
    delete editor;

    m_network.Stop();
}

QString AudioToMidiBlock::getName()
{
    return "Audio To MIDI";
}

QString AudioToMidiBlock::getGroupName()
{
    return "CLAM Blocks";
}

QWidget* AudioToMidiBlock::getEditorWidget()
{
    return editor;
}

iControlBlock* AudioToMidiBlock::createDefaultBlock()
{
    return new AudioToMidiBlock();
}

void AudioToMidiBlock::setChord(QString chordName)
{
    if (editorUi->le_chordDisplay->text() == chordName)
    {
        return;
    }

    editorUi->le_chordDisplay->setText(chordName);

    foreach(QByteArray note, m_chordNotes)
    {
        note[0] = 128;
        emit sendChord(note);
    }
    m_chordNotes.clear();

    QStringList chordTokens = chordName.split(' ');
    QString baseNote = chordTokens.front();
    int baseNoteOffset = m_baseNoteMap.value(baseNote, 0);

    QList<char> defaultList;
    defaultList.push_back(0);

    QString chordType = chordName.mid(baseNote.size()+1);
    QList<char> chordOffsets = m_chordNoteMap.value(chordType, defaultList);

    QList<char> notes;

    foreach (char offset, chordOffsets)
    {
        notes.push_back((static_cast<int>(offset)+static_cast<int>(baseNoteOffset))%12);
    }


    foreach(char note, notes)
    {
        QByteArray noteOn;
        noteOn.push_back(static_cast<char>(144));
        noteOn.push_back(static_cast<char>(note));
        noteOn.push_back(static_cast<char>(100));

        m_chordNotes.push_back(noteOn);
        emit sendChord(noteOn);
    }
}

void AudioToMidiBlock::setNotes(QByteArray notes)
{
    foreach(QByteArray note, m_noteNotes)
    {
        note[0] = 128;
        emit sendNotes(note);
    }
    m_noteNotes.clear();

    QString noteList = "";

    foreach(char note, notes)
    {
        QByteArray noteOn;
        noteOn.push_back(static_cast<char>(144));
        noteOn.push_back(static_cast<char>(note));
        noteOn.push_back(static_cast<char>(100));

        noteList += QString::number(static_cast<int>(note)) + ",";

        m_noteNotes.push_back(noteOn);
        emit sendNotes(noteOn);
    }

    editorUi->le_notes->setText(noteList);
}
