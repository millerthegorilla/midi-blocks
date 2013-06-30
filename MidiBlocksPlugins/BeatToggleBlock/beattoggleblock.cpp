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

#include "beattoggleblock.h"
#include "ui_beattoggleblockeditor.h"

BeatToggleBlock::BeatToggleBlock(QObject *parent) :
    editorUi(new Ui::BeatToggleBlockEditor)
{
    if (parent)
    {
        setParent(parent);
    }
    
    editor = new QWidget();
    editorUi->setupUi(editor);

    m_first = true;
}

BeatToggleBlock::~BeatToggleBlock()
{
    delete editorUi;
    delete editor;
}

QString BeatToggleBlock::getName()
{
    return "Beat Toggle";
}

QString BeatToggleBlock::getGroupName()
{
    return "Beat Blocks";
}

QWidget* BeatToggleBlock::getEditorWidget()
{
    return editor;
}

ControlBlock* BeatToggleBlock::createDefaultBlock()
{
    return new BeatToggleBlock();
}

void BeatToggleBlock::receiveBeat(QByteArray message)
{
    if (m_first)
    {
        emit sendFirst_Beat(message);
        m_first = false;
    }
    else
    {
        emit sendSecond_Beat(message);
        m_first = true;
    }
}

Q_EXPORT_PLUGIN2(beattoggleblockplugin, BeatToggleBlock)

