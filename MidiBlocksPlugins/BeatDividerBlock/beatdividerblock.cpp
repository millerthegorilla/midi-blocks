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

#include "beatdividerblock.h"
#include "ui_beatdividerblockeditor.h"

BeatDividerBlock::BeatDividerBlock(QObject *parent) :
    editorUi(new Ui::BeatDividerBlockEditor)
{
    if (parent)
    {
        setParent(parent);
    }
    
    editor = new QWidget();
    editorUi->setupUi(editor);

    m_beats = 0;
}

BeatDividerBlock::~BeatDividerBlock()
{
    delete editorUi;
    delete editor;
}

QString BeatDividerBlock::getName()
{
    return "Beat Divider Block";
}

QString BeatDividerBlock::getGroupName()
{
    return "My Control Blocks";
}

QWidget* BeatDividerBlock::getEditorWidget()
{
    return editor;
}

ControlBlock* BeatDividerBlock::createDefaultBlock()
{
    return new BeatDividerBlock();
}

void BeatDividerBlock::receiveBeat(QByteArray message)
{
    Q_UNUSED(message)

    m_beats++;

    if (m_beats >= editorUi->sb_factor->value())
    {
        m_beats = 0;
        emit sendBeat(QByteArray());
    }
}

Q_PLUGIN_METADATA(beatdividerblockplugin, BeatDividerBlock)

