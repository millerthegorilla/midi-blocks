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

#include "transposeblock.h"
#include "ui_transposeblockeditor.h"
#include <QDebug>

TransposeBlock::TransposeBlock(QObject *parent) :
    editorUi(new Ui::TransposeBlockEditor)
{
    if (parent)
    {
        setParent(parent);
    }

    for (int i = 0; i<128; i++)
    {
        m_transposeReference[i]=0;
        m_noteOriginLookup[i]=0;
    }
    
    editor = new QWidget();
    editorUi->setupUi(editor);

    for (int i = 0; i<12; i++)
    {
        m_allowableNoteCounts[i] = 0;
    }

    setupConsonantMap();
}

TransposeBlock::~TransposeBlock()
{
    delete editorUi;
    delete editor;
}

QString TransposeBlock::getName()
{
    return "Transpose Block";
}

QString TransposeBlock::getGroupName()
{
    return "Modification Blocks";
}

QWidget* TransposeBlock::getEditorWidget()
{
    return editor;
}

void TransposeBlock::receiveInput(QByteArray message)
{
    if (message.size() == 3)
    {
        //check for note on
        if (message.at(0) == static_cast<char>(144))
        {
            //non zero velocity is a note on
            if (message.at(2) != 0)
            {
                uchar pressedNote = static_cast<uchar>(message.at(1));
                uchar transposedNote = transposeNote(pressedNote);

                if (transposedNote <= 127)
                {
                    m_transposeReference[pressedNote] = transposedNote;
                    m_noteOriginLookup[transposedNote] = pressedNote;

                    m_activeNotes.insert(transposedNote);

                    message[1] = transposedNote;

                    sendOutput(message);
                }
                else
                {
                    m_overflowNotes.insert(pressedNote);
                    sendOverflow(message);
                }
            }
            //if the velocity is 0, it is a note off
            else
            {
                if (m_overflowNotes.contains(static_cast<uchar>(message.at(1))))
                {
                    sendOverflow(message);
                    m_overflowNotes.remove(static_cast<uchar>(message.at(1)));
                }
                else
                {
                    m_activeNotes.remove(m_transposeReference[static_cast<uchar>(message.at(1))]);
                    message[1] = m_transposeReference[static_cast<uchar>(message.at(1))];
                    sendOutput(message);
                }
            }
        }
        //check for note off
        else if (message.at(0) == static_cast<char>(128))
        {
            if (m_overflowNotes.contains(static_cast<uchar>(message.at(1))))
            {
                sendOverflow(message);
                m_overflowNotes.remove(static_cast<uchar>(message.at(1)));
            }
            else
            {
                m_activeNotes.remove(m_transposeReference[static_cast<uchar>(message.at(1))]);
                message[1] = m_transposeReference[static_cast<uchar>(message.at(1))];
                sendOutput(message);
            }
        }
    }
    else
    {
        sendOutput(message);
    }
}

void TransposeBlock::receiveAllowable_Notes(QByteArray message)
{
    if (message.size() == 3)
    {
        //check for note on
        if (message.at(0) == static_cast<char>(144))
        {
            unsigned char pressedNote = static_cast<uchar>(message.at(1));

            //non zero velocity is a note on
            if (message.at(2) != 0)
            {
                m_allowableNoteCounts[pressedNote%12]++;
                setupConsonantMap();
            }
            //if the velocity is 0, it is a note off
            else
            {
                m_allowableNoteCounts[pressedNote%12]--;
                setupConsonantMap();
            }
        }
        //check for note off
        else if (message.at(0) == static_cast<char>(128))
        {
            unsigned char pressedNote = static_cast<uchar>(message.at(1));

            m_allowableNoteCounts[pressedNote%12]--;
            setupConsonantMap();
        }
    }
}

void TransposeBlock::setupConsonantMap()
{
    unsigned char consonantMap[12];
    bool allZero = true;

    for (int i = 0; i<12; i++)
    {
        consonantMap[i] = 13;

        if (m_allowableNoteCounts[i] != 0)
        {
            allZero = false;
        }
    }

    if (allZero)
    {
        QString display;
        for (int i = 0; i<12; i++)
        {
            m_consonantMap[i] = i;
            display += QString::number(static_cast<uint>(m_consonantMap[i])) + " ";
        }
        editorUi->plainTextEdit->clear();
        editorUi->plainTextEdit->appendPlainText(display);

        return;
    }

    bool incomplete = true;
    while (incomplete)
    {
        incomplete = false;
        for (int i = 0; i<12; i++)
        {
            if (consonantMap[i] == 13)
            {
                if (m_allowableNoteCounts[i] > 0)
                {
                    consonantMap[i] = i;

                    int before = (i==0) ? 11 : i-1;
                    if (m_allowableNoteCounts[before] == 0 && consonantMap[before] == 13)
                    {
                        consonantMap[before] = i;
                    }

                    int after = (i+1)%12;
                    if (m_allowableNoteCounts[after] == 0 && consonantMap[after] == 13)
                    {
                        consonantMap[after] = i;
                        i++;
                    }
                }
                else
                {
                    int after = (i+1)%12;
                    if (consonantMap[after] != 13)
                    {
                        consonantMap[i] = consonantMap[after];
                        i++;
                    }
                    else
                    {
                        incomplete = true;
                    }
                }
            }
        }
    }

    QString display;
    for (int i = 0; i<12; i++)
    {
        m_consonantMap[i] = consonantMap[i];
        display += QString::number(static_cast<uint>(m_consonantMap[i])) + " ";
    }

    editorUi->plainTextEdit->clear();
    editorUi->plainTextEdit->appendPlainText(display);
}

unsigned char TransposeBlock::transposeNote(const unsigned char& note)
{
    //get a transposed note
    unsigned char transposedNote = (note/12)*12 + m_consonantMap[note%12];

    if (m_activeNotes.contains(transposedNote))
    {
        unsigned char alreadyPressedNote = m_noteOriginLookup[transposedNote];

        int modifier = (alreadyPressedNote > note) ? -12 : 12;

        transposedNote += modifier;
        while (m_activeNotes.contains(transposedNote))
        {
            transposedNote += modifier;
        }
    }

    return transposedNote;
}

Q_PLUGIN_METADATA(transposeblockplugin, TransposeBlock)

