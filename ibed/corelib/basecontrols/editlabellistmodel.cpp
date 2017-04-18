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
**  @file     editlabellistmodel.cpp
**  @brief    edit label list model class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "editlabellistitem.h"
#include "editlabellistview.h"
#include "editlabellistmodel.h"


class EditLabelListModelPrivate
{
public:
    QList<EditLabelListItem *> m_items;
};

EditLabelListModel::EditLabelListModel(QObject *parent) :
    QAbstractListModel(parent),
    d_ptr(new EditLabelListModelPrivate)
{
}

EditLabelListModel::~EditLabelListModel()
{
    while(d_ptr->m_items.count())
        delete d_ptr->m_items.takeAt(0);
    delete d_ptr;
}


void EditLabelListModel::itemChanged(EditLabelListItem *item)
{
    int itemIndex = d_ptr->m_items.indexOf(item);
    if(itemIndex >= 0)
        emit dataChanged(index(itemIndex), index(itemIndex));
}


int EditLabelListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return d_ptr->m_items.count();
}

QVariant EditLabelListModel::data(const QModelIndex &index, int role) const
{
    if((!index.isValid()) && (index.row() >= d_ptr->m_items.count()))
        return QVariant();

    return d_ptr->m_items.at(index.row())->data(role);
}

bool EditLabelListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_D(EditLabelListModel);
    if((!index.isValid()) && (index.row() >= d->m_items.count()))
        return false;


    d->m_items.at(index.row())->setData(role, value);
    if(role == Qt::EditRole)
    {
        d->m_items.at(index.row())->setData(Qt::DisplayRole, value);
    }

    return true;
}

Qt::ItemFlags EditLabelListModel::flags(const QModelIndex &index) const
{
    if((!index.isValid()) && (index.row() >= d_ptr->m_items.count()))
        return 0;

    return (Qt::ItemIsEditable | Qt::ItemIsEnabled);
}

bool EditLabelListModel::insertRow(int row, EditLabelListItem *item)
{
    beginInsertRows(QModelIndex(), row, row);

    d_ptr->m_items.insert(row, item);

    endInsertRows();

    return true;
}

bool EditLabelListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    for(int pos = row; pos < (row + count); ++pos)
    {
        d_ptr->m_items.insert(pos, new EditLabelListItem());
    }
    endInsertRows();
    return true;
}

bool EditLabelListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    EditLabelListItem *item = NULL;
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

EditLabelListItem *EditLabelListModel::item(int row) const
{
    if(row < d_ptr->m_items.count())
        return d_ptr->m_items.at(row);

    return NULL;
}

EditLabelListItem *EditLabelListModel::item(const QModelIndex &index) const
{
    if(index.row() < d_ptr->m_items.count())
        return d_ptr->m_items.at(index.row());

    return NULL;
}

QList<EditLabelListItem *> EditLabelListModel::allItems() const
{
    return d_ptr->m_items;
}
