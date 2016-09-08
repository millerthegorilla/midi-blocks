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

#include "chorditemdelegate.h"
#include <QLineEdit>
#include <QStringList>

ChordItemDelegate::ChordItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget* ChordItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    return new QLineEdit(parent);
}

void ChordItemDelegate::setEditorData(QWidget *editor, const QModelIndex& index ) const
{
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);

    if (lineEdit)
    {
        QList<QVariant> values = index.data(Qt::EditRole).toList();
        QString valuesString;

        foreach (QVariant value, values)
        {
            valuesString.push_back(value.toString()+ ",");
        }

        lineEdit->setText(valuesString);
    }
}

void ChordItemDelegate::setModelData(QWidget *editor, QAbstractItemModel* model, const QModelIndex& index ) const
{
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);

    if (lineEdit)
    {
        QList<QVariant> values;
        QStringList valueStrings = lineEdit->text().split(',', QString::SkipEmptyParts);

        foreach (QString value, valueStrings)
        {
            values.push_back(value);
        }

        model->setData(index, values);
    }
}

void ChordItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    Q_UNUSED(index)
    editor->setGeometry(QRect(option.rect.topLeft(), editor->sizeHint()));
}
