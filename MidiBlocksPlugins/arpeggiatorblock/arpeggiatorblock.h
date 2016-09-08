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

#ifndef ARPEGGIATORBLOCK_H
#define ARPEGGIATORBLOCK_H

#include "controlblock.h"
#include <QtWidgets/QWidget>

namespace Ui {
class ArpeggiatorBlockEditor;
}

class ArpeggiatorBlock : public ControlBlock
{
    Q_OBJECT
    Q_INTERFACES(ControlBlock)
    
public:
    explicit ArpeggiatorBlock(QObject* parent = 0);
    ~ArpeggiatorBlock();
    
    QString getName();
    QString getGroupName();
    
    QWidget* getEditorWidget();
    ControlBlock* createDefaultBlock();
    
signals:
    //Prefix visible outputs with "send"
    void sendOutput(QByteArray message);
    
public slots:
    //Prefix visible inputs with "receive"
    void receiveAllowable_Notes(QByteArray message);
    void receiveNote_On(QByteArray message);
    void receiveNote_Off(QByteArray message);
    
private:
    Ui::ArpeggiatorBlockEditor* editorUi;
    QWidget* editor;

    QList<QByteArray> m_noteList;
    QByteArray m_currentNote;
    int m_currentIndex;
};

#endif // ARPEGGIATORBLOCK_H


