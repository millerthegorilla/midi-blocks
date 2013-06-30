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

#ifndef BEATTOGGLEBLOCK_H
#define BEATTOGGLEBLOCK_H

#include "controlblock.h"
#include <QWidget>

namespace Ui {
class BeatToggleBlockEditor;
}

class BeatToggleBlock : public ControlBlock
{
    Q_OBJECT
    Q_INTERFACES(ControlBlock)
    
public:
    explicit BeatToggleBlock(QObject* parent = 0);
    ~BeatToggleBlock();
    
    QString getName();
    QString getGroupName();
    
    QWidget* getEditorWidget();
    ControlBlock* createDefaultBlock();
    
signals:
    //Prefix visible outputs with "send"
    void sendFirst_Beat(QByteArray message);
    void sendSecond_Beat(QByteArray message);
    
public slots:
    //Prefix visible inputs with "receive"
    void receiveBeat(QByteArray message);
    
private:
    Ui::BeatToggleBlockEditor* editorUi;
    QWidget* editor;

    bool m_first;
};

#endif // BEATTOGGLEBLOCK_H


