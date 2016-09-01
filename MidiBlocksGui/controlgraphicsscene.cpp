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

#include "controlgraphicsscene.h"
#include "connection.h"
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>
#include <QMimeData>
#include <QTransform>
#include <QPluginLoader>
/*#include "pluginlistmodel.h"*/

ControlGraphicsScene::ControlGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    m_currSenderItem = NULL;
    m_currSignalIndex = 0;
    m_items.clear();
}

ControlGraphicsScene::~ControlGraphicsScene()
{
//    foreach (ControlBlockGraphicsItem* item, m_items)
//    {
//        removeItem(item);
//    }
//    qDeleteAll(m_items);
    m_currSenderItem = NULL;
    m_currSignalIndex = 0;
    m_items.clear();
}

void ControlGraphicsScene::addControlBlock(ControlBlock* block, QPointF pos)
{
    ControlBlockGraphicsItem* item = new ControlBlockGraphicsItem();
    item->setControlBlock(block);

    addItem(item);
    item->setPos(pos);

    m_items.insert(item);

    update();
}

void ControlGraphicsScene::initiateConnection(ControlBlockGraphicsItem* item, int signalIndex)
{
    // keep track of the sender and index for later use
    m_currSenderItem = item;
    m_currSignalIndex = signalIndex;

    update();
}

void ControlGraphicsScene::completeConnection(ControlBlockGraphicsItem* item, int slotIndex)
{
    // attempt to connect the sender's signal to the reciever's slot
    if (m_currSenderItem)
    {
        Connection* connection = new Connection();
        if (connection->createConnection(m_currSenderItem, m_currSignalIndex,
                                         item, slotIndex))
        {
            // add the connection graphics item to the scene
            this->addItem(connection);
            update();
        }
        else
        {
            // the connection failed
            delete connection;
        }
    }
}

void ControlGraphicsScene::clearConnectionState()
{
    m_currSenderItem = 0;
    m_currSignalIndex = 0;
}

void ControlGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();

//    if(views().size() > 0)
//        {
//            QGraphicsView* v = views().at(0);
//            t = v->transform();
//        }
    ControlBlockGraphicsItem* item =
            dynamic_cast<ControlBlockGraphicsItem*>(this->itemAt(event->scenePos(), QTransform()));

    if (item)
    {
        int indexAtPos = item->outputAtPos(pos);
        if (indexAtPos >= 0)
        {
            m_currSenderItem = item;
            m_currSignalIndex = indexAtPos;
            item->setHighlight(indexAtPos);
            event->ignore();
            return;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void ControlGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();
//    QTransform t;
//    if(views().size() > 0)
//        {
//            QGraphicsView* v = views().at(0);
//            t = v->transform();
//        }
    ControlBlockGraphicsItem* item =
            dynamic_cast<ControlBlockGraphicsItem*>(this->itemAt(event->scenePos(), QTransform()));

    if (item && m_currSenderItem)
    {
        int indexAtPos = item->inputAtPos(pos);
        if (indexAtPos >= 0)
        {
            completeConnection(item, indexAtPos);
            event->ignore();
        }
    }
    else
    {
        QGraphicsScene::mouseReleaseEvent(event);
    }

    // clear connection state (there is no longer a connection being made)
    clearConnectionState();
}

void ControlGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();
    ControlBlockGraphicsItem* item =
            dynamic_cast<ControlBlockGraphicsItem*>(this->itemAt(event->scenePos(),QTransform()));

    foreach (ControlBlockGraphicsItem* cbitem, m_items)
    {
        if (cbitem != m_currSenderItem)
        {
            cbitem->clearHighlights();
        }
    }

    if (item)
    {
        if (m_currSenderItem)
        {
            int indexAtPos = item->inputAtPos(pos);
            if (indexAtPos >= 0)
            {
                item->setHighlight(indexAtPos);
            }
        }
        else
        {
            int indexAtPos = item->outputAtPos(pos);
            if (indexAtPos >= 0)
            {
                item->setHighlight(indexAtPos);
            }
        }

        update();
    }

    QGraphicsScene::mouseMoveEvent(event);
}


void ControlGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        QGraphicsItem *item = focusItem();

        if (item)
        {
            //destroy if it is a block
            ControlBlockGraphicsItem* block = dynamic_cast<ControlBlockGraphicsItem*>(item);
            if (block)
            {
                m_items.remove(block);
                setFocusItem(0);
                this->removeItem(item);
                delete item;

                // clear connection state (in case the sender was deleted)
                clearConnectionState();

                update();
            }

            //destroy if it is a connection
            Connection* connection = dynamic_cast<Connection*>(item);
            if (connection)
            {
                setFocusItem(0);
                this->removeItem(item);
                delete item;

                update();
            }
        }

    }
    else
    {
        QGraphicsScene::keyPressEvent(event);
    }
}

void ControlGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("text/pluginfile"))
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void ControlGraphicsScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();
}

void ControlGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("text/pluginfile"))
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void ControlGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (!event->mimeData()->hasFormat("text/pluginfile"))
    {
        event->ignore();
        return;
    }

    QString fileName = event->mimeData()->data("text/pluginfile");
    event->accept();

    if (fileName == "")
    {
        foreach (QObject *plugin, QPluginLoader::staticInstances())
        {
            ControlBlock *block = qobject_cast<ControlBlock*>(plugin);
            if (block)
            {
                if (block->getName() == event->mimeData()->text())
                {
                    addControlBlock(block->createDefaultBlock(), event->scenePos());
                    break;
                }
            }
        }
    }
    else
    {
        QPluginLoader loader(fileName);

        QObject *plugin = loader.instance();
        if (plugin)
        {
            ControlBlock *block = qobject_cast<ControlBlock*>(plugin);
            if (block)
            {
                addControlBlock(block->createDefaultBlock(), event->scenePos());
            }
        }
    }
}
