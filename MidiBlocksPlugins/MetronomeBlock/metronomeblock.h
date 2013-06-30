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

#ifndef METRONOMEBLOCK_H
#define METRONOMEBLOCK_H

#include "controlblock.h"
#include <QWidget>
#include <QTimer>

namespace Ui {
class MetronomeBlockEditor;
}

class MetronomeBlock : public ControlBlock
{
    Q_OBJECT
    Q_INTERFACES(ControlBlock)
    
public:
    explicit MetronomeBlock(QObject* parent = 0);
    ~MetronomeBlock();
    
    QString getName();
    QString getGroupName();
    
    QWidget* getEditorWidget();
    ControlBlock* createDefaultBlock() {return new MetronomeBlock();}
    
signals:
    //Prefix visible outputs with "send"
    void sendBeat(QByteArray message);
    
public slots:
    //Prefix visible inputs with "receive"
    void prepareBeat();

private slots:
    void setBpm(double value);
    
private:
    Ui::MetronomeBlockEditor* editorUi;
    QWidget* editor;

    unsigned char m_activeNote;

    QTimer m_timer;
};

#endif // METRONOMEBLOCK_H


