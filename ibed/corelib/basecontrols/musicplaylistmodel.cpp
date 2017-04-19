/*****************************************************************************
**
**  Copyright (C) 2016-2017 HuangYang
**
**  This file is part of IBED
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License version 3 as
**  published by the Free Software Foundation.
**
**  You should have received a copy of the GNU General Public License
**  along with this program. If not, see <http://www.gnu.org/licenses/>.
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
**
**  @file     musicplaylistmodel.cpp
**  @brief    music play list model class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "musicplaylistitem.h"
#include "musicplaylistview.h"
#include "musicplaylistmodel.h"

class MusicPlayListModelPrivate
{
public:
    ~MusicPlayListModelPrivate();
public:
    QList<MusicPlayListItem *> m_items;
};

MusicPlayListModel::MusicPlayListModel(QObject *parent) :
    QAbstractListModel(parent),
    d_ptr(new MusicPlayListModelPrivate)
{
}

MusicPlayListModel::~MusicPlayListModel()
{
    delete d_ptr;
}


void MusicPlayListModel::itemChanged(MusicPlayListItem *item)
{
    int itemIndex = d_ptr->m_items.indexOf(item);
    if(itemIndex >= 0)
        emit dataChanged(index(itemIndex), index(itemIndex));
}


int MusicPlayListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return d_ptr->m_items.count();
}

QVariant MusicPlayListModel::data(const QModelIndex &index, int role) const
{
    if((!index.isValid()) && (index.row() >= d_ptr->m_items.count()))
        return QVariant();

    return d_ptr->m_items.at(index.row())->data(role);
}

bool MusicPlayListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_D(MusicPlayListModel);
    if((!index.isValid()) && (index.row() >= d->m_items.count()))
        return false;


    d->m_items.at(index.row())->setData(role, value);

    return true;
}

Qt::ItemFlags MusicPlayListModel::flags(const QModelIndex &index) const
{
    if((!index.isValid()) && (index.row() >= d_ptr->m_items.count()))
        return 0;

    return Qt::ItemIsEnabled;
}

bool MusicPlayListModel::insertRow(int row, MusicPlayListItem *item)
{
    beginInsertRows(QModelIndex(), row, row);

    d_ptr->m_items.insert(row, item);

    endInsertRows();

    return true;
}

bool MusicPlayListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    for(int pos = row; pos < (row + count); ++pos)
    {
        d_ptr->m_items.insert(pos, new MusicPlayListItem());
    }
    endInsertRows();
    return true;
}

bool MusicPlayListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    MusicPlayListItem *item = NULL;
    beginRemoveRows(parent, row, row + count - 1);

    while(count--)
    {
        item = d_ptr->m_items.takeAt(row);
        if(item != NULL)
            delete item;
    }

    endRemoveRows();
    return true;
}

MusicPlayListItem *MusicPlayListModel::item(int row) const
{
    if(row < d_ptr->m_items.count())
        return d_ptr->m_items.at(row);

    return NULL;
}

MusicPlayListItem *MusicPlayListModel::item(const QModelIndex &index) const
{
    if(index.row() < d_ptr->m_items.count())
        return d_ptr->m_items.at(index.row());

    return NULL;
}

QList<MusicPlayListItem *> MusicPlayListModel::allItems() const
{
    return d_ptr->m_items;
}


MusicPlayListModelPrivate::~MusicPlayListModelPrivate()
{
    while(m_items.count())
        delete m_items.takeAt(0);
}
