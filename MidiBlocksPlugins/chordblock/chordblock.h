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

#ifndef CHORDBLOCK_H
#define CHORDBLOCK_H

#include "../interfacedef/controlblockinterface.h"
#include <QtWidgets/QWidget>

namespace Ui {
class ChordBlockEditor;
}

class ChordBlock : public iControlBlock
{
    Q_PLUGIN_METADATA(IID "org.MidiBlocks.MidiBlocksPlugins.ChordBlock")
    Q_INTERFACES(iControlBlock)
    
public:
    explicit ChordBlock(QObject* parent = 0);
    ~ChordBlock();
    
    QString getName();
    QString getGroupName();
    
    QWidget* getEditorWidget();
    iControlBlock* createDefaultBlock();
    
signals:
    //Prefix visible outputs with "send"
    void sendOutput(QByteArray message);
    
public slots:
    //Prefix visible inputs with "receive"
    //void receiveTonic(QByteArray message);
    //void receiveScale_Degree(QByteArray message);
    //void receiveTchordblockrigger(QByteArray message);
    
private:
    Ui::ChordBlockEditor* editorUi;
    QWidget* editor;
};

#endif // CHORDBLOCK_H


