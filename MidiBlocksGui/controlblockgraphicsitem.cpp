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

#include "controlblockgraphicsitem.h"
#include <QPainter>
#include <QMetaObject>
#include <QMetaMethod>
#include <QtWidgets/QGraphicsSceneHoverEvent>
#include <QDebug>

ControlBlockGraphicsItem::ControlBlockGraphicsItem(/*QGraphicsItem *parent*/) //:
    //QGraphicsObject (parent)
{
    m_block = 0;
    m_proxyWidget = new QGraphicsProxyWidget(this);

    m_proxyWidget->setPos(0, 30);

    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemIsFocusable);

    this->setAcceptHoverEvents(true);

    m_blockWidth = 100;
    m_blockHeight = 100;
    m_highlightedInOut = "";
}

ControlBlockGraphicsItem::~ControlBlockGraphicsItem()
{
    m_proxyWidget->setWidget(0);
    emit destroyConnections();
}

void ControlBlockGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    int editorWidth = m_proxyWidget->size().width();
    int inputWidth = 0;
    int outputWidth = 0;

    int editorHeight = m_proxyWidget->size().height();
    int inputHeight = 0;
    int outputHeight = 0;
    int headerHeight = 30;

    int inOutHeight = 20;

    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);

    foreach (QString in, m_inputs)
    {
        if (painter->fontMetrics().width(in) + 5 > inputWidth)
        {
            inputWidth = painter->fontMetrics().width(in) + 5;
        }
        inputHeight += inOutHeight;
    }
    foreach (QString out, m_outputs)
    {
        if (painter->fontMetrics().width(out) + 5 > outputWidth)
        {
            outputWidth = painter->fontMetrics().width(out) + 5;
        }
        outputHeight += inOutHeight;
    }

    m_proxyWidget->setPos(inputWidth, headerHeight);

    m_blockWidth = editorWidth + inputWidth + outputWidth;
    m_blockHeight = qMax(qMax(inputHeight, outputHeight), editorHeight) + headerHeight + 5;

    painter->setPen(Qt::transparent);
    painter->setBrush(QColor(220, 220, 220));
    painter->drawRect(QRect(0, 0, m_blockWidth, m_blockHeight));
    painter->setBrush(QColor(80, 80, 80));
    painter->drawRect(QRect(0, 0, m_blockWidth, headerHeight));



    if (m_block)
    {

        QTextOption titleOption(Qt::AlignCenter);
        QTextOption inputOption(Qt::AlignVCenter|Qt::AlignLeft);
        QTextOption outputOption(Qt::AlignVCenter|Qt::AlignRight);


        painter->setPen(Qt::black);
        painter->setBrush(Qt::lightGray);

        for (int i =0; i<m_inputs.count(); i++)
        {
            m_inOutRects[m_inputs.at(i)] = QRect(0,
                                                 headerHeight+i*inOutHeight,
                                                 inputWidth,
                                                 inOutHeight);

            if (m_inputs.at(i) == m_highlightedInOut)
            {
                painter->setPen(Qt::transparent);
                painter->setBrush(Qt::darkGray);

                painter->drawRect(m_inOutRects.value(m_inputs.at(i)));
                painter->setPen(Qt::white);
                painter->drawText(m_inOutRects.value(m_inputs.at(i)), m_inputs.at(i), inputOption);

                painter->setPen(Qt::black);
                painter->setBrush(Qt::lightGray);
            }
            else
            {
                painter->drawText(m_inOutRects.value(m_inputs.at(i)), m_inputs.at(i), inputOption);
            }
        }
         for (int i =0; i<m_outputs.count(); i++)
        {
             m_inOutRects[m_outputs.at(i)] = QRect(inputWidth+editorWidth,
                                                   headerHeight+i*inOutHeight,
                                                   outputWidth,
                                                   inOutHeight);

             if (m_outputs.at(i) == m_highlightedInOut)
             {
                 painter->setPen(Qt::transparent);
                 painter->setBrush(Qt::darkGray);

                 painter->drawRect(m_inOutRects.value(m_outputs.at(i)));
                 painter->setPen(Qt::white);
                 painter->drawText(m_inOutRects.value(m_outputs.at(i)), m_outputs.at(i), outputOption);

                 painter->setPen(Qt::black);
                 painter->setBrush(Qt::lightGray);
             }
             else
             {
                painter->drawText( m_inOutRects.value(m_outputs.at(i)), m_outputs.at(i), outputOption);
             }
        }

         QFont headerFont("Monospace", 10, QFont::Bold);
         painter->setFont(headerFont);
         painter->setPen(Qt::white);
        painter->drawText(QRect(0, 0, m_blockWidth, headerHeight), m_block->getName(), titleOption);
    }

    if (this->hasFocus())
    {
        painter->setPen(QPen(QColor(40, 130, 230), 2));
        painter->setBrush(Qt::transparent);

        painter->drawRect(0, 0, m_blockWidth, m_blockHeight);
    }
}

QRectF ControlBlockGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, m_blockWidth, m_blockHeight);
}

void ControlBlockGraphicsItem::setControlBlock(ControlBlock* block)
{
    m_block = block;
    m_proxyWidget->setWidget(block->getEditorWidget());
    m_proxyWidget->setPos(0, 30);

    m_inputs.clear();
    m_outputs.clear();

    //Get the inputs and outputs from the meta object
    const QMetaObject* metaObject = m_block->metaObject();
    QMetaMethod method;
    for (int i = 0; i<metaObject->methodCount(); i++)
    {
        method = metaObject->method(i);
        QString signature = metaObject->normalizedSignature(method.methodSignature());
        if (method.methodType() == QMetaMethod::Signal && signature.startsWith("send"))
        {
            QString name = signature.mid(4, signature.indexOf('(')-4);
            name.replace('_', " ");
            name.append("->");

            m_methodIndices.insert(name, i);

            m_outputs << name;
        }
        else if (method.methodType() == QMetaMethod::Slot && signature.startsWith("receive"))
        {
            QString name = signature.mid(7, signature.indexOf('(')-7);
            name.replace('_', " ");
            name.push_front("->");

            m_methodIndices.insert(name, i);

            m_inputs << name;
        }
    }
}

QRectF ControlBlockGraphicsItem::getConnectionRect(int methodIndex) const
{
    QString method = m_methodIndices.key(methodIndex, "");

    if (method.isEmpty())
    {
        return QRectF();
    }

    return m_inOutRects.value(method);

}

int ControlBlockGraphicsItem::inputAtPos(QPointF pos)
{
    foreach (QString input, m_inputs)
    {
        if (m_inOutRects.value(input).contains(mapFromScene(pos).toPoint()))
        {
            return m_methodIndices.value(input, -1);
        }
    }

    return -1;
}

int ControlBlockGraphicsItem::outputAtPos(QPointF pos)
{
    foreach (QString output, m_outputs)
    {
        if (m_inOutRects.value(output).contains(mapFromScene(pos).toPoint()))
        {
            return m_methodIndices.value(output, -1);
        }
    }

    return -1;
}

void ControlBlockGraphicsItem::setHighlight(int index)
{
    m_highlightedInOut = m_methodIndices.key(index, "");
}

void ControlBlockGraphicsItem::clearHighlights()
{
    m_highlightedInOut = "";
}
