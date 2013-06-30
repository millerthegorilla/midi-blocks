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

#include "virtualinblock.h"
#include "ui_virtualinblockeditor.h"

VirtualInBlock::VirtualInBlock(QObject *parent) :
    editorUi(new Ui::VirtualInBlockEditor)
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
        m_virtualIn = new RtMidiOut();
        m_virtualIn->openVirtualPort("Virtual MIDI In");
    }
    catch (RtError &error)
    {
        m_virtualIn = 0;
    }
}

VirtualInBlock::~VirtualInBlock()
{
    if (m_virtualIn)
    {
        m_virtualIn->closePort();
        delete m_virtualIn;
    }
    delete editorUi;
    delete editor;
}

QString VirtualInBlock::getName()
{
    return "VirtualInBlock";
}

QString VirtualInBlock::getGroupName()
{
    return "I/O Blocks";
}

QWidget* VirtualInBlock::getEditorWidget()
{
    return editor;
}

ControlBlock* VirtualInBlock::createDefaultBlock()
{
    return new VirtualInBlock();
}

void VirtualInBlock::receiveMIDI(QByteArray message)
{
    if (!m_virtualIn)
    {
        return;
    }

    std::vector<unsigned char> vectorMessage;
    foreach(char c, message)
    {
        vectorMessage.push_back(static_cast<unsigned char>(c));
    }
    m_virtualIn->sendMessage(&vectorMessage);
}

Q_EXPORT_PLUGIN2(virtualinblockplugin, VirtualInBlock)

