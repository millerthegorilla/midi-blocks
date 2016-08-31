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

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtWidgets/QGraphicsObject>
#include "controlblockgraphicsitem.h"

/*!

\class Connection connection.h
\brief Manages a single connection between two modules

Provides a visual and deletable representation of a connection between
modules in a ControlGraphicsScene.

\see ControlGraphicsScene

*/
class Connection : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Connection(QGraphicsItem *parent = 0);
    ~Connection();

    /// Creates a connection between two control blocks
    bool createConnection(ControlBlockGraphicsItem* sender, int sendIndex,
                          ControlBlockGraphicsItem* receiver, int receiveIndex);


    /// Draws the connection
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /// Returns the bounding rectangle of the QPainterPath returned by Connection::shape()
    QRectF boundingRect() const;

    /// Returns a reasonable bounding area for clicking/selecting in the graphics view
    QPainterPath shape() const;

protected:
    
signals:
    
private slots:
    /// Breaks the connection that is currently being maintained
    void breakExistingConnection();

    /// Destroy this Connection (in the case that a connect-ee has been destroyed)
    void forgetConnection();

private:
    ControlBlockGraphicsItem* m_sender;
    int m_sendIndex;

    ControlBlockGraphicsItem* m_receiver;
    int m_receiveIndex;

    //This is useless extravagence?
    bool m_broken;
};

#endif // CONNECTION_H
