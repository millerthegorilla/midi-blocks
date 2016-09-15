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

#include "metronomeblock.h"
#include "ui_metronomeblockeditor.h"

MetronomeBlock::MetronomeBlock(QObject *parent) :
    editorUi(new Ui::MetronomeBlockEditor)
{
    if (parent)
    {
        setParent(parent);
    }
    
    editor = new QWidget();
    editorUi->setupUi(editor);

    connect(&m_timer, SIGNAL(timeout()),
            this, SLOT(prepareBeat()));

    connect(editorUi->sb_bpm, SIGNAL(valueChanged(double)),
            this, SLOT(setBpm(double)));

    m_timer.setInterval(60000.0/120.0);

    m_timer.start();
}

MetronomeBlock::~MetronomeBlock()
{
    m_timer.stop();
    delete editorUi;
    delete editor;
}

QString MetronomeBlock::getName()
{
    return "Metronome";
}

QString MetronomeBlock::getGroupName()
{
    return "Time Blocks";
}

QWidget* MetronomeBlock::getEditorWidget()
{
    return editor;
}

void MetronomeBlock::setBpm(double value)
{
    m_timer.setInterval(60000.0/value);
}

void MetronomeBlock::prepareBeat()
{
    emit sendBeat(QByteArray());
}

iControlBlock* MetronomeBlock::createDefaultBlock()
{
    return new MetronomeBlock();
}
