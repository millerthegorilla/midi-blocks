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

#ifndef CONTROLGRAPHICSSCENE_H
#define CONTROLGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include "controlblock.h"
#include "controlblockgraphicsitem.h"

/*!

\class ControlGraphicsScene controlblockgraphicsscene.h
\brief A QGraphicsScene made to display ControlBlockGraphicsItems

Provides an area for displaying, manipulating, and connecting
ControlBlockGraphicsItems

\see ControlBlockGraphicsItem ControlBlock

*/
class ControlGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ControlGraphicsScene(QObject *parent = 0);
    virtual ~ControlGraphicsScene();

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void addControlBlock(ControlBlock* block, QPointF pos);
    void removeSelectedControlBlock();
    
signals:
    
public slots:
    void initiateConnection(ControlBlockGraphicsItem* item, int signalIndex);
    void completeConnection(ControlBlockGraphicsItem* item, int slotIndex);

private:
    void clearConnectionState();

    QSet<ControlBlockGraphicsItem*> m_items;

    ControlBlockGraphicsItem* m_currSenderItem;
    int m_currSignalIndex;

};

#endif // CONTROLGRAPHICSSCENE_H
