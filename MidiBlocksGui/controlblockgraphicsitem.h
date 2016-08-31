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

#ifndef CONTROLBLOCKGRAPHICSITEM_H
#define CONTROLBLOCKGRAPHICSITEM_H

#include <QtWidgets/QGraphicsObject>
#include "controlblock.h"
#include <QtWidgets/QGraphicsProxyWidget>


/*!

\class ControlBlockGraphicsItem controlblockgraphicsitem.h
\brief Graphical view wrapper for a ControlBlock

Provides the graphical representation of a ControlBlock for a
ControlGraphicsScene.

\see ControlGraphicsScene ControlBlock

*/
class ControlBlockGraphicsItem : public QGraphicsObject
{
    Q_OBJECT
public:
    ControlBlockGraphicsItem();
    ~ControlBlockGraphicsItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void setControlBlock(ControlBlock* block);

    int inputAtPos(QPointF pos);
    int outputAtPos(QPointF pos);

    void setHighlight(int index);
    void clearHighlights();

    QRectF getConnectionRect(int methodIndex) const;
    ControlBlock* getControlBlock() {return m_block;}

signals:
    void destroyConnections();

public slots:


private:
    ControlBlock* m_block;
    QGraphicsProxyWidget* m_proxyWidget;

    QList<QString> m_inputs;
    QList<QString> m_outputs;

    QHash<QString, QRect> m_inOutRects;
    QHash<QString, int> m_methodIndices;

    QString m_highlightedInOut;

    int m_blockWidth;
    int m_blockHeight;
};

#endif // CONTROLBLOCKGRAPHICSITEM_H
