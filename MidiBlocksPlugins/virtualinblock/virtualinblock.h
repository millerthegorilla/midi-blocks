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

#ifndef VIRTUALINBLOCK_H
#define VIRTUALINBLOCK_H

#include "RtMidi.h"
#include "../interfacedef/controlblockinterface.h"
#include <QtWidgets/QWidget>

namespace Ui {
class VirtualInBlockEditor;
}

class VirtualInBlock : public iControlBlock
{
    Q_PLUGIN_METADATA(IID "org.MidiBlocks.MidiBlocksPlugins.ChordBlock")
    Q_INTERFACES(iControlBlock)

public:
    explicit VirtualInBlock(QObject* parent = 0);
    ~VirtualInBlock();
    
    QString getName();
    QString getGroupName();
    
    QWidget* getEditorWidget();
    iControlBlock* createDefaultBlock();
    
signals:
    //Prefix visible outputs with "send"
    
public slots:
    //Prefix visible inputs with "receive"
    void receiveMIDI(QByteArray message);
    
private:
    Ui::VirtualInBlockEditor* editorUi;
    QWidget* editor;
    RtMidiOut* m_virtualIn;
};

#endif // VIRTUALINBLOCK_H


