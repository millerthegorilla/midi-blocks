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

#ifndef BEATDIVIDERBLOCK_H
#define BEATDIVIDERBLOCK_H

#include "../interfacedef/controlblockinterface.h"
#include <QtWidgets/QWidget>

namespace Ui {
class BeatDividerBlockEditor;
}

class BeatDividerBlock : public QObject, public iControlBlock
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "MidiBlocks.MidiBlocksPlugins.iControlBlock")
    Q_INTERFACES(iControlBlock)

public:
    explicit BeatDividerBlock(QObject* parent = 0);
    ~BeatDividerBlock();
    
    QString getName();
    QString getGroupName();
    
    QWidget* getEditorWidget();
    iControlBlock* createDefaultBlock();
    
signals:
    //Prefix visible outputs with "send"
    void sendBeat(QByteArray message);
    
public slots:
    //Prefix visible inputs with "receive"
    void receiveBeat(QByteArray message);
    
private:
    Ui::BeatDividerBlockEditor* editorUi;
    QWidget* editor;

    int m_beats;
};

#endif // BEATDIVIDERBLOCK_H


