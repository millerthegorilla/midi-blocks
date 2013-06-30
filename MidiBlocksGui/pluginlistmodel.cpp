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

#include "pluginlistmodel.h"
#include <QMimeData>
#include <QStringList>

PluginListModel::PluginListModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

QVariant PluginListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return m_plugins.at(index.row());
    }
    else if (role == Qt::UserRole)
    {
        return m_pluginFileNameMap.value(m_plugins.at(index.row()));
    }

    return QVariant();
}

Qt::ItemFlags PluginListModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
    {
        return (Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    }

    return Qt::NoItemFlags;
}

QMimeData *PluginListModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData* mimeData = new QMimeData();

    QModelIndex oneIndex = indexes.first();

    if (oneIndex.isValid())
    {
        mimeData->setText(oneIndex.data(Qt::DisplayRole).toString());
        mimeData->setData("text/pluginfile", oneIndex.data(Qt::UserRole).toByteArray());
    }

    return mimeData;
}

QStringList PluginListModel::mimeTypes() const
{
    QStringList types;
    types << "text/pluginfile";
    return types;
}

int PluginListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_plugins.size();
}

void PluginListModel::addPlugin(QString name, QString absoluteFileName)
{
    beginInsertRows(QModelIndex(), m_pluginFileNameMap.size(), m_pluginFileNameMap.size());
    m_plugins.push_back(name);
    m_pluginFileNameMap.insert(name, absoluteFileName);
    endInsertRows();
}
