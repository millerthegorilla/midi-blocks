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

#include "channelblock.h"
#include "ui_channelblockeditor.h"

ChannelBlock::ChannelBlock(QObject *parent) :
    editorUi(new Ui::ChannelBlockEditor)
{
    if (parent)
    {
        setParent(parent);
    }
    
    editor = new QWidget();
    editorUi->setupUi(editor);

    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QChannelBlock" FILE "channelblock.json")
}

ChannelBlock::~ChannelBlock()
{
    delete editorUi;
    delete editor;
}

QString ChannelBlock::getName()
{
    return "Channel Block";
}

QString ChannelBlock::getGroupName()
{
    return "Utility Blocks";
}

QWidget* ChannelBlock::getEditorWidget()
{
    return editor;
}

ControlBlock* ChannelBlock::createDefaultBlock()
{
    return new ChannelBlock();
}

void ChannelBlock::receiveInput(QByteArray message)
{
    if (message.size() == 3)
    {
        //check for note on
        if (static_cast<uchar>(message.at(0)) >= 144 && static_cast<uchar>(message.at(0)) <= 159)
        {
            message[0] = static_cast<char>(144+editorUi->spinBox->value()-1);
        }
        //check for note off
        else if (static_cast<uchar>(message.at(0)) >= 128 && static_cast<uchar>(message.at(0)) <= 143)
        {
            message[0] = static_cast<char>(128+editorUi->spinBox->value()-1);
        }
    }

    emit sendOutput(message);
}

//Q_PLUGIN_METADATA(channelblockplugin, ChannelBlock)

