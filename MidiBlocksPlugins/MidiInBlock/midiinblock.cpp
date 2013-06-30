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

#include "midiinblock.h"
#include "ui_midiinblockeditor.h"
#include <QDebug>

MidiInBlock::MidiInBlock(QObject *parent) :
    editorUi(new Ui::MidiInBlockEditor)
{
    if (parent)
    {
        setParent(parent);
    }
    
    editor = new QWidget();
    editorUi->setupUi(editor);

    //Set Up MIDI Input
    try
    {
        m_midiIn = new RtMidiIn();
        m_midiIn->setCallback( &MidiInBlock::inputCallback , static_cast<void*>(this));
        m_midiIn->ignoreTypes();
    }
    catch (RtError &error)
    {
        m_midiIn = 0;
    }

    probeMidiIns();
}

MidiInBlock::~MidiInBlock()
{
    delete editorUi;
    delete editor;
}

QString MidiInBlock::getName()
{
    return "MIDI In";
}

QString MidiInBlock::getGroupName()
{
    return "I/O Blocks";
}

QWidget* MidiInBlock::getEditorWidget()
{
    return editor;
}

void MidiInBlock::changeInput(int index)
{
    if (!m_midiIn)
    {
        return;
    }

    m_midiIn->closePort();

    //index 0 is always no port
    if (index == 0)
    {
        return;
    }

    if (index > m_inputs.size())
    {
        editorUi->cb_portSelect->setCurrentIndex(0);
        return;
    }

    index--;

    if (m_inputs.at(index) == "ERROR")
    {
        editorUi->cb_portSelect->setCurrentIndex(0);
        return;
    }

    try
    {
        m_midiIn->openPort(index);
    }
    catch (RtError &error)
    {
        editorUi->cb_portSelect->setCurrentIndex(0);
        return;
    }
}

void MidiInBlock::probeMidiIns()
{
    if (!m_midiIn)
    {
        return;
    }

    disconnect(editorUi->cb_portSelect, SIGNAL(currentIndexChanged(int)),
               this, SLOT(changeInput(int)));
    m_inputs.clear();
    editorUi->cb_portSelect->clear();
    editorUi->cb_portSelect->addItem("No Input");

    m_midiIn->closePort();

    //Scan for input ports
    unsigned int nPorts;

    nPorts = m_midiIn->getPortCount();
    for ( unsigned int i=0; i<nPorts; i++ )
    {
        try
        {
            QString name = m_midiIn->getPortName(i).c_str();
            m_inputs.push_back(name);
        }
        catch ( RtError &error )
        {
            m_inputs.push_back("ERROR");
        }
    }

    editorUi->cb_portSelect->addItems(m_inputs);

    connect(editorUi->cb_portSelect, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeInput(int)));
}

void MidiInBlock::inputCallback(double deltatime, std::vector< unsigned char > *message, void *userData)
{
    MidiInBlock* specificBlock = static_cast<MidiInBlock*>(userData);

    if (specificBlock)
    {
        specificBlock->input(deltatime, message);
    }
}

void MidiInBlock::input(double deltatime, std::vector< unsigned char > *message)
{
    Q_UNUSED(deltatime)

    QByteArray messageCopy;

    for (unsigned int i=0; i<message->size(); i++)
    {
        messageCopy.push_back(message->at(i));
    }

    emit sendInput(messageCopy);
}
Q_EXPORT_PLUGIN2(midiinblockplugin, MidiInBlock)

