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

#ifndef CHORDBANKMODEL_H
#define CHORDBANKMODEL_H

#include <QAbstractTableModel>
#include <QSet>

struct ChordData
{
    QList<QVariant> notes;
    unsigned int duration;
    unsigned int currBeat;
};

class ChordBankModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ChordBankModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

    QList<QVariant> getChordForBeat();

signals:
    
public slots:
    void incrementBeat();

private:
    QList<ChordData*> m_chordData;
    int m_currIndex;
};

#endif // CHORDBANKMODEL_H
