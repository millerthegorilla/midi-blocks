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

#ifndef MIDIOUTBLOCK_H
#define MIDIOUTBLOCK_H

#include "RtMidi.h"
#include "controlblock.h"
#include <QtWidgets/QWidget>
#include <QList>

namespace Ui {
class MidiOutBlockEditor;
}

class MidiOutBlock : public ControlBlock
{
    Q_OBJECT
    Q_INTERFACES(ControlBlock)
    
public:
    explicit MidiOutBlock(QObject* parent = 0);
    ~MidiOutBlock();
    
    QString getName();
    QString getGroupName();
    
    QWidget* getEditorWidget();
    ControlBlock* createDefaultBlock() {return new MidiOutBlock();}
    
signals:
    //Prefix visible outputs with "send"
    
public slots:
    //Prefix visible inputs with "receive"
    void receiveMIDI(QByteArray message);

private slots:
    void changeOutput(int index);
    void probeMidiOuts();
    
private:
    Ui::MidiOutBlockEditor* editorUi;
    QWidget* editor;

    RtMidiOut *m_midiOut;
    QList<QString> m_outputs;
};

#endif // MIDIOUTBLOCK_H


