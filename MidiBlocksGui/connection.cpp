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

#include "connection.h"
#include <QPainter>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QDebug>

Connection::Connection(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    m_sender = NULL;
    m_receiver = NULL;
    m_sendIndex = -1;
    m_receiveIndex = -1;

    setFlags(QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemIsFocusable);

    //setAcceptsHoverEvents(true);

    setPos(0,0);

    m_broken = false;
}

void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (m_sender && m_receiver && !m_broken)
    {
        QPen normal(Qt::black, 2);
        QPen highlighted(QColor(40, 130, 230), 3);

        painter->setPen(this->hasFocus() ? highlighted : normal);
        painter->drawLine(mapFromScene(
                              m_sender->mapToScene(
                                  QPointF(m_sender->getConnectionRect(m_sendIndex).right(),
                                          m_sender->getConnectionRect(m_sendIndex).center().y()))),
                          mapFromScene(
                              m_receiver->mapToScene(
                                  QPointF(m_receiver->getConnectionRect(m_receiveIndex).left(),
                                          m_receiver->getConnectionRect(m_receiveIndex).center().y()))));
    }
}

QRectF Connection::boundingRect() const
{
    return shape().boundingRect();
}

Connection::~Connection()
{
    breakExistingConnection();
}

bool Connection::createConnection(ControlBlockGraphicsItem* sender, int sendIndex,
                                  ControlBlockGraphicsItem* receiver, int receiveIndex)
{
    breakExistingConnection();
    m_broken = false;

    m_sender = sender;
    m_sendIndex = sendIndex;
    m_receiver = receiver;
    m_receiveIndex = receiveIndex;


    connect(m_sender, SIGNAL(destroyed()),
            this, SLOT(forgetConnection()));
    connect(m_receiver, SIGNAL(destroyed()),
            this, SLOT(forgetConnection()));

    m_broken = connect(m_sender->getControlBlock(), m_sender->getm_sendIndex,
                                     m_receiver->getControlBlock(), m_receiveIndex);

    return !m_broken;
}

void Connection::breakExistingConnection()
{
    if (m_sender && m_receiver && !m_broken)
    {
        QMetaObject::disconnect(m_sender->getControlBlock(), m_sendIndex,
                                m_receiver->getControlBlock(), m_receiveIndex);

        m_sender = 0;
        m_receiver = 0;

        m_broken = true;
    }
}

void Connection::forgetConnection()
{
    m_sender = 0;
    m_receiver = 0;

    m_broken = true;

    deleteLater();
}

QPainterPath Connection::shape() const
{
    if (m_sender && m_receiver && !m_broken)
    {
        QRectF sender = mapFromScene(m_sender->mapToScene(m_sender->getConnectionRect(m_sendIndex)).boundingRect()).boundingRect();
        QRectF receiver = mapFromScene(m_receiver->mapToScene(m_receiver->getConnectionRect(m_receiveIndex)).boundingRect()).boundingRect();

        QPainterPath path(sender.topRight());
        path.lineTo(sender.bottomRight());
        path.lineTo(receiver.bottomLeft());
        path.lineTo(receiver.topLeft());
        path.closeSubpath();

        return path;
    }
    else
    {
        return QPainterPath();
    }
}
