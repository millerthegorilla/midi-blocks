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

#include "chordbankmodel.h"

ChordBankModel::ChordBankModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_currIndex = 0;
}

int ChordBankModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_chordData.size();
}

int ChordBankModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant ChordBankModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
        {
            QString valuesString;

            foreach (QVariant value, m_chordData.at(index.row())->notes)
            {
                valuesString.push_back(value.toString()+ ",");
            }

            return valuesString;
        }
        else if (index.column() == 1)
        {
            return m_chordData.at(index.row())->duration;
        }
        else if (index.column() == 2)
        {
            if (m_chordData.at(index.row())->currBeat > 0)
            {
                return m_chordData.at(index.row())->currBeat;
            }
        }
    }
    else if (role == Qt::EditRole)
    {
        if (index.column() == 0)
        {
            return m_chordData.at(index.row())->notes;
        }
        else if (index.column() == 1)
        {
            return m_chordData.at(index.row())->duration;
        }
    }

    return QVariant();
}

QVariant ChordBankModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if (section == 0)
        {
            return "Notes";
        }
        else if (section == 1)
        {
            return "Beats";
        }
        else if (section == 2)
        {
            return "Count";
        }
    }

    return QVariant();
}

bool ChordBankModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        if (index.column() == 0)
        {
            m_chordData.at(index.row())->notes = value.toList();
            return true;
        }
        else if (index.column() == 1)
        {
            m_chordData.at(index.row())->duration = value.toUInt();
            return true;
        }
    }

    return false;
}

Qt::ItemFlags ChordBankModel::flags(const QModelIndex &index) const
{
    if (index.column() < 2)
    {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool ChordBankModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (row > m_chordData.size())
    {
        return false;
    }
    else
    {
        beginInsertRows(parent, row, row+count-1);
        for (int i = 0; i<count; i++)
        {
            ChordData *data = new ChordData;
            data->duration = 1;
            data->currBeat = 0;
            data->notes.clear();
            data->notes.push_back(0);
            data->notes.push_back(4);
            data->notes.push_back(7);
            m_chordData.insert(row, data);
        }
        endInsertRows();
        return true;
    }
}

bool ChordBankModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row+count > m_chordData.size())
    {
        return false;
    }
    else
    {
        beginRemoveRows(parent, row, row+count);
        for (int i = 0; i<count; i++)
        {
            delete m_chordData.takeAt(row);
        }
        endRemoveRows();
        return true;
    }
}

QList<QVariant> ChordBankModel::getChordForBeat()
{
    if (m_currIndex < m_chordData.size())
    {
        return m_chordData.at(m_currIndex)->notes;
    }
    else
    {
        return QList<QVariant>();
    }
}

void ChordBankModel::incrementBeat()
{
    if (m_currIndex < m_chordData.size())
    {
        m_chordData.at(m_currIndex)->currBeat++;
        if (m_chordData.at(m_currIndex)->currBeat > m_chordData.at(m_currIndex)->duration)
        {
            m_chordData.at(m_currIndex)->currBeat = 0;
            m_currIndex = (m_currIndex+1)%m_chordData.size();
            m_chordData.at(m_currIndex)->currBeat++;
        }

        emit dataChanged(this->index(0, 2, QModelIndex()),
                         this->index(this->rowCount(QModelIndex())-1, 2, QModelIndex()));
    }
}
