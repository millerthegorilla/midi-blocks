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

#include "arpeggiatorblock.h"
#include "ui_arpeggiatorblockeditor.h"

ArpeggiatorBlock::ArpeggiatorBlock(QObject *parent) :
    editorUi(new Ui::ArpeggiatorBlockEditor)
{
    if (parent)
    {
        setParent(parent);
    }
    
    editor = new QWidget();
    editorUi->setupUi(editor);

    editorUi->cb_mode->addItem("Random");
    editorUi->cb_mode->addItem("Ascending");
    editorUi->cb_mode->addItem("Descending");

    m_currentIndex = 0;
}

ArpeggiatorBlock::~ArpeggiatorBlock()
{
    delete editorUi;
    delete editor;
}

QString ArpeggiatorBlock::getName()
{
    return "Arpeggiator Block";
}

QString ArpeggiatorBlock::getGroupName()
{
    return "Modification Blocks";
}

QWidget* ArpeggiatorBlock::getEditorWidget()
{
    return editor;
}

iControlBlock *ArpeggiatorBlock::createDefaultBlock()
{
    return new ArpeggiatorBlock();
}

bool noteLessThan(const QByteArray& a, const QByteArray& b)
{
    if (a.size() == 3 && b.size() == 3)
    {
        return (a.at(1) < b.at(1));
    }
    else
    {
        return false;
    }
}

void ArpeggiatorBlock::receiveAllowable_Notes(QByteArray message)
{
    if (message.size() == 3)
    {
        //check for note on
        if (message.at(0) == static_cast<char>(144))
        {
            //non zero velocity is a note on
            if (message.at(2) != 0)
            {
                m_noteList.push_back(message);
                qSort(m_noteList.begin(), m_noteList.end(), noteLessThan);
            }
            //if the velocity is 0, it is a note off
            else
            {
                for(int i = 0; i<m_noteList.size(); i++)
                {
                    if (message.at(1) == m_noteList.at(i).at(1))
                    {
                        m_noteList.removeAt(i);
                        i--;
                    }
                }
            }
        }
        //check for note off
        else if (message.at(0) == static_cast<char>(128))
        {
            for(int i = 0; i<m_noteList.size(); i++)
            {
                if (message.at(1) == m_noteList.at(i).at(1))
                {
                    m_noteList.removeAt(i);
                    i--;
                }
            }
        }
    }
}

void ArpeggiatorBlock::receiveNote_On(QByteArray message)
{
    Q_UNUSED(message)

    if (m_currentNote.size() > 0)
    {
        m_currentNote[0] = static_cast<char>(128);
        sendOutput(m_currentNote);
        m_currentNote.clear();
    }

    if (m_noteList.size() > 0)
    {
        if (editorUi->cb_mode->currentText() == "Ascending")
        {
            if (++m_currentIndex >= m_noteList.size())
            {
                m_currentIndex = 0;
            }
        }
        else if (editorUi->cb_mode->currentText() == "Descending")
        {
            if (--m_currentIndex < 0)
            {
                m_currentIndex = m_noteList.size()-1;
            }
        }
        else
        {
            m_currentIndex = qrand()%m_noteList.size();
        }

        m_currentNote = m_noteList.at(m_currentIndex);
        sendOutput(m_currentNote);
    }
}

void ArpeggiatorBlock::receiveNote_Off(QByteArray message)
{
    Q_UNUSED(message)

    if (m_currentNote.size() > 0)
    {
        m_currentNote[0] = static_cast<char>(128);
        sendOutput(m_currentNote);
        m_currentNote.clear();
    }
}
