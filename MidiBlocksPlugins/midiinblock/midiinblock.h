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

#ifndef MIDIINBLOCK_H
#define MIDIINBLOCK_H

#include "../interfacedef/controlblockinterface.h"
#include <QtWidgets/QWidget>
#include "RtMidi.h"
#include <QTimer>

namespace Ui {
class MidiInBlockEditor;
}

class MidiInBlock : public QObject, public iControlBlock
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "MidiBlocks.MidiBlocksPlugins.iControlBlock")
    Q_INTERFACES(iControlBlock)

public:
    explicit MidiInBlock(QObject* parent = 0);
    ~MidiInBlock();
    
    QString getName();
    QString getGroupName();
    
    QWidget* getEditorWidget();
    iControlBlock* createDefaultBlock() {return new MidiInBlock();}

    static void inputCallback( double deltatime, std::vector< unsigned char > *message, void *userData );
    void input(double deltatime, std::vector< unsigned char > *message);
    
signals:
    //Prefix visible outputs with "send"
    void sendInput(QByteArray message);
    
public slots:
    //Prefix visible inputs with "receive"

private slots:
    void changeInput(int index);
    void probeMidiIns();
    
private:
    Ui::MidiInBlockEditor* editorUi;
    QWidget* editor;

    RtMidiIn *m_midiIn;

    QList<QString> m_inputs;
};

#endif // MIDIINBLOCK_H


