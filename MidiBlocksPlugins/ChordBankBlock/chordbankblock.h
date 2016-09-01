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

#ifndef CHORDBANKBLOCK_H
#define CHORDBANKBLOCK_H

#include "controlblock.h"
#include <QtWidgets/QWidget>
#include "chordbankmodel.h"
#include "chordeditor.h"

namespace Ui {
class ChordBankBlockEditor;
}

class ChordBankBlock : public ControlBlock
{
    Q_OBJECT
    Q_INTERFACES(ControlBlock)
    
public:
    explicit ChordBankBlock(QObject* parent = 0);
    ~ChordBankBlock();
    
    QString getName();
    QString getGroupName();
    
    QWidget* getEditorWidget();
    ControlBlock* createDefaultBlock();
    
signals:
    //Prefix visible outputs with "send"
    void sendChord(QByteArray message);

public slots:
    //Prefix visible inputs with "receive"
    void receiveBeat(QByteArray message);
//    void receiveToggle_Write_Mode(QByteArray message);
//    void receiveWrite_Input(QByteArray message);

private slots:
    void addChord();
    void removeChord();

private:
    Ui::ChordBankBlockEditor* editorUi;
    QWidget* editor;

    QList<QByteArray> m_notes;

    ChordBankModel m_model;
    ChordEditor m_chordEditor;
};

#endif // CHORDBANKBLOCK_H


