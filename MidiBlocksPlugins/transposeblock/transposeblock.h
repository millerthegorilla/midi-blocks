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

#ifndef TRANSPOSEBLOCK_H
#define TRANSPOSEBLOCK_H

#include "../interfacedef/controlblockinterface.h"
#include <QtWidgets/QWidget>
#include <QSet>

namespace Ui {
class TransposeBlockEditor;
}

class TransposeBlock : public iControlBlock
{
    Q_OBJECT
    Q_INTERFACES(iControlBlock)
    Q_PLUGIN_METADATA(IID "org.MidiBlocks.MidiBlocksPlugins.TransposeBlock")

public:
    explicit TransposeBlock(QObject* parent = 0);
    ~TransposeBlock();
    
    QString getName();
    QString getGroupName();
    
    QWidget* getEditorWidget();
    iControlBlock* createDefaultBlock() {return new TransposeBlock();}
    
signals:
    //Prefix visible outputs with "send"
    void sendOutput(QByteArray message);
    void sendOverflow(QByteArray message);
    
public slots:
    //Prefix visible inputs with "receive"
    void receiveInput(QByteArray message);
    void receiveAllowable_Notes(QByteArray message);
    
private:
    Ui::TransposeBlockEditor* editorUi;
    QWidget* editor;

    unsigned char transposeNote(const unsigned char &note);
    void setupConsonantMap();

    QSet<unsigned char> m_activeNotes;
    QSet<unsigned char> m_overflowNotes;
    unsigned char m_transposeReference[128];
    unsigned char m_noteOriginLookup[128];

    unsigned char m_consonantMap[12];
    unsigned int m_allowableNoteCounts[12];
};

#endif // TRANSPOSEBLOCK_H


