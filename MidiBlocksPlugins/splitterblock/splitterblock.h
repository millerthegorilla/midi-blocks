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

#ifndef SPLITTERBLOCK_H
#define SPLITTERBLOCK_H

#include "../interfacedef/controlblockinterface.h"
#include <QtWidgets/QWidget>

namespace Ui {
class SplitterBlockEditor;
}

class SplitterBlock : public iControlBlock
{
    Q_OBJECT
    Q_INTERFACES(iControlBlock)
    Q_PLUGIN_METADATA(IID "org.MidiBlocks.MidiBlocksPlugins.SplitterBlock")

public:
    explicit SplitterBlock(QObject* parent = 0);
    ~SplitterBlock();
    
    QString getName();
    QString getGroupName();
    
    QWidget* getEditorWidget();
    iControlBlock* createDefaultBlock() {return new SplitterBlock();}
    
signals:
    //Prefix visible outputs with "send"
    void sendFirst_Out(QByteArray message);
    void sendSecond_Out(QByteArray message);

public slots:
    //Prefix visible inputs with "receive"
    void receiveInput(QByteArray message);
    
private:
    Ui::SplitterBlockEditor* editorUi;
    QWidget* editor;
};

#endif // SPLITTERBLOCK_H


