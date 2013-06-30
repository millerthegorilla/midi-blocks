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

#include "chordeditor.h"
#include "ui_chordeditor.h"

//QList<char> chromatic = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
//QList<char> ionian = {0, 0, 2, 4, 4, 5, 7, 7, 7, 9, 11, 11};
//QList<char> dorian = {0, 0, 2, 3, 3, 5, 7, 7, 7, 9, 10, 10};
//QList<char> phrygian = {0, 1, 1, 3, 3, 5, 7, 7, 8, 8, 10, 10};
//QList<char> lydian = {0, 0, 2, 4, 4, 6, 7, 7, 7, 9, 11, 11};
//QList<char> mixolydian = {0, 0, 2, 4, 4, 5, 7, 7, 7, 9, 10, 10};
//QList<char> aeolian = {0, 0, 2, 3, 3, 5, 7, 7, 8, 8, 10, 10};
//QList<char> locrian = {0, 1, 1, 3, 3, 5, 6, 6, 8, 8, 10, 10};

ChordEditor::ChordEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChordEditor)
{
    ui->setupUi(this);

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

    m_chordNoteMap.insert("Major", majorTriad);
    m_chordNoteMap.insert("Dominant7", dominant7);
    m_chordNoteMap.insert("Major7", major7);
    m_chordNoteMap.insert("Minor", minorTriad);
    m_chordNoteMap.insert("Minor6", minor6);
    m_chordNoteMap.insert("Minor7", minor7);
    m_chordNoteMap.insert("Minor7-5", minor7flat5);
    m_chordNoteMap.insert("Minor-5", dimTriad);
    m_chordNoteMap.insert("Power", powerChord);

    ui->cb_chordType->addItems(QStringList(m_chordNoteMap.keys()));

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

    ui->cb_baseNote->addItems(QStringList(m_baseNoteMap.keys()));

    connect(ui->cb_baseNote, SIGNAL(currentIndexChanged(int)),
            this, SLOT(adjustToParameters()));
    connect(ui->cb_chordType, SIGNAL(currentIndexChanged(int)),
            this, SLOT(adjustToParameters()));
    connect(ui->sb_min, SIGNAL(valueChanged(int)),
            this, SLOT(adjustToParameters()));
    connect(ui->sb_max, SIGNAL(valueChanged(int)),
            this, SLOT(adjustToParameters()));
}

ChordEditor::~ChordEditor()
{
    delete ui;
}

void ChordEditor::setValues(QList<QVariant> values)
{
    m_values = values;
}

QList<QVariant> ChordEditor::getValues() const
{
    return m_values;
}

void ChordEditor::adjustToParameters()
{
    m_values.clear();

    if (ui->sb_min->value() > ui->sb_max->value())
    {
        ui->sb_min->setValue(ui->sb_max->value());
    }

    int min = ui->sb_min->value();
    int max = ui->sb_max->value();
    int baseNote = m_baseNoteMap.value(ui->cb_baseNote->currentText(), 0);
    QList<char> chordNotes = m_chordNoteMap.value(ui->cb_chordType->currentText(), QList<char>());
    QSet<char> chordNotesSet = chordNotes.toSet();

    for (int i = min; i<=max; i++)
    {
        int testNote = i-baseNote;
        if (testNote >= 0)
        {
            if (chordNotesSet.contains(testNote%12))
            {
                m_values.push_back(i);
            }
        }
    }
}
