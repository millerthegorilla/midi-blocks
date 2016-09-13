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

#include "splitterblock.h"
#include "ui_splitterblockeditor.h"

SplitterBlock::SplitterBlock(QObject *parent) :
    editorUi(new Ui::SplitterBlockEditor)
{
    if (parent)
    {
        setParent(parent);
    }
    
    editor = new QWidget();
    editorUi->setupUi(editor);

    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QSplitterBlock")
}

SplitterBlock::~SplitterBlock()
{
    delete editorUi;
    delete editor;
}

QString SplitterBlock::getName()
{
    return "Splitter Block";
}

QString SplitterBlock::getGroupName()
{
    return "Flow Blocks";
}

QWidget* SplitterBlock::getEditorWidget()
{
    return editor;
}

void SplitterBlock::receiveInput(QByteArray message)
{
    if (message.size() == 3)
    {
        //check for note on
        if (message.at(0) == static_cast<char>(144) || message.at(0) == static_cast<char>(128))
        {
            unsigned char pressedNote = static_cast<uchar>(message.at(1));

            if (pressedNote >= editorUi->sb_splitNote->value())
            {
                emit sendSecond_Out(message);
            }
            else
            {
                emit sendFirst_Out(message);
            }
        }
    }
}

//Q_PLUGIN_METADATA(splitterblockplugin, SplitterBlock)
