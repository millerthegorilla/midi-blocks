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

#ifndef AUDIOTOMIDIBLOCK_H
#define AUDIOTOMIDIBLOCK_H

#include "controlblock.h"
#include <QWidget>
#include <QMap>

#include "CLAM/Network.hxx"


namespace Ui {
class AudioToMidiBlockEditor;
}

class AudioToMidiBlock : public ControlBlock
{
    Q_OBJECT
    Q_INTERFACES(ControlBlock)
    
public:
    explicit AudioToMidiBlock(QObject* parent = 0);
    ~AudioToMidiBlock();
    
    QString getName();
    QString getGroupName();
    
    QWidget* getEditorWidget();
    ControlBlock* createDefaultBlock();
    
signals:
    //Prefix visible outputs with "send"
    void sendChord(QByteArray message);
    void sendNotes(QByteArray message);
    
public slots:
    //Prefix visible inputs with "receive"

private slots:
    void setChord(QString chordName);
    void setNotes(QByteArray notes);
    
private:
    Ui::AudioToMidiBlockEditor* editorUi;
    QWidget* editor;

    QList<QByteArray> m_chordNotes;
    QList<QByteArray> m_noteNotes;

    QMap<QString, char> m_baseNoteMap;
    QMap<QString, QList<char> > m_chordNoteMap;

    CLAM::Network m_network;
};

#endif // AUDIOTOMIDIBLOCK_H


