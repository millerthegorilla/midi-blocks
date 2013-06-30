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

#include "midioutblock.h"
#include "ui_midioutblockeditor.h"

MidiOutBlock::MidiOutBlock(QObject *parent) :
    editorUi(new Ui::MidiOutBlockEditor)
{
    if (parent)
    {
        setParent(parent);
    }
    
    editor = new QWidget();
    editorUi->setupUi(editor);

    //Set Up MIDI Output
    try
    {
        m_midiOut = new RtMidiOut();
    }
    catch (RtError &error)
    {
        m_midiOut = 0;
    }

    probeMidiOuts();
}

MidiOutBlock::~MidiOutBlock()
{
    if (m_midiOut)
    {
        m_midiOut->closePort();
        delete m_midiOut;
    }
    delete editorUi;
    delete editor;
}

QString MidiOutBlock::getName()
{
    return "MIDI Output";
}

QString MidiOutBlock::getGroupName()
{
    return "I/O Blocks";
}

QWidget* MidiOutBlock::getEditorWidget()
{
    return editor;
}

void MidiOutBlock::changeOutput(int index)
{
    if (!m_midiOut)
    {
        return;
    }

    m_midiOut->closePort();

    //index 0 is always no port
    if (index == 0)
    {
        return;
    }

    if (index > m_outputs.size())
    {
        editorUi->cb_portSelect->setCurrentIndex(0);
        return;
    }

    index--;

    if (m_outputs.at(index) == "ERROR")
    {
        editorUi->cb_portSelect->setCurrentIndex(0);
        return;
    }

    try
    {
        m_midiOut->openPort(index);
    }
    catch (RtError &error)
    {
        editorUi->cb_portSelect->setCurrentIndex(0);
        return;
    }
}

void MidiOutBlock::probeMidiOuts()
{
    if (!m_midiOut)
    {
        return;
    }

    disconnect(editorUi->cb_portSelect, SIGNAL(currentIndexChanged(int)),
               this, SLOT(changeOutput(int)));
    m_outputs.clear();
    editorUi->cb_portSelect->clear();
    editorUi->cb_portSelect->addItem("No Output");

    m_midiOut->closePort();

    //Scan for output ports
    unsigned int nPorts;

    nPorts = m_midiOut->getPortCount();
    for ( unsigned int i=0; i<nPorts; i++ )
    {
        try
        {
            QString name = m_midiOut->getPortName(i).c_str();
            m_outputs.push_back(name);
        }
        catch ( RtError &error )
        {
            m_outputs.push_back("ERROR");
        }
    }

    editorUi->cb_portSelect->addItems(m_outputs);

    connect(editorUi->cb_portSelect, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeOutput(int)));
}

void MidiOutBlock::receiveMIDI(QByteArray message)
{
    if (!m_midiOut || editorUi->cb_portSelect->currentIndex() == 0)
    {
        return;
    }

    std::vector<unsigned char> vectorMessage;
    foreach(char c, message)
    {
        vectorMessage.push_back(static_cast<unsigned char>(c));
    }
    m_midiOut->sendMessage(&vectorMessage);
}

Q_EXPORT_PLUGIN2(midioutblockplugin, MidiOutBlock)

