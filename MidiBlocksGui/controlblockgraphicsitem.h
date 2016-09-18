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
#include "../MidiBlocksPlugins/interfacedef/controlblockinterface.h"
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
    ControlBlockGraphicsItem(/*QGraphicsItem *parent = 0*/);
    ~ControlBlockGraphicsItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void setControlBlock(iControlBlock* block);

    int inputAtPos(QPointF pos);
    int outputAtPos(QPointF pos);

    void setHighlight(int index);
    void clearHighlights();

    //quick hack to get it working

    QRectF getConnectionRect(int methodIndex) const;
    iControlBlock* getControlBlock() {return m_block;}

signals:
    void destroyConnections();

public slots:


private:
    iControlBlock* m_block;
    QGraphicsProxyWidget* m_proxyWidget;

    enum connectionType {
        signal = 0x01,
        slot = 0x02,
    };

    struct m_connectionInfo {
        QString name;
        QMetaMethod method;
    };

    QList<QString> m_inputs;
    QList<QString> m_outputs;

    QHash<m_connectionInfo, QRect> m_inOutRects;
    QHash<m_connectionInfo, int> m_connection;

    bool m_highlightedInOut;

    int m_blockWidth;
    int m_blockHeight;
};

#endif // CONTROLBLOCKGRAPHICSITEM_H
