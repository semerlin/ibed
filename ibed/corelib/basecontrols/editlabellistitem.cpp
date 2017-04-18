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
**  @file     editlabellistitem.cpp
**  @brief    edit label list item class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "editlabellistview.h"
#include "editlabellistmodel.h"
#include "editlabellistitem.h"
#include "editlabellistview_p.h"
#include "editlabellistitem_p.h"


EditLabelListItem::EditLabelListItem() :
    d(new EditLabelListItemPrivate())
{
    int alignment = Qt::AlignVCenter | Qt::AlignLeft;
    setData(Qt::TextAlignmentRole, alignment);
    setData(Qt::UserRole + 2, 1);
    setData(Qt::UserRole + 3, 1);
    setData(Qt::UserRole + 4, 1);
}

EditLabelListItem::EditLabelListItem(const QString &name, const QString &text,
                                     const QString &extraName) :
    d(new EditLabelListItemPrivate())
{
    setData(Qt::UserRole, name);
    setData(Qt::DisplayRole, text);
    setData(Qt::UserRole + 1, extraName);
    int alignment = Qt::AlignVCenter | Qt::AlignLeft;
    setData(Qt::TextAlignmentRole, alignment);
    setData(Qt::UserRole + 2, 1);
    setData(Qt::UserRole + 3, 1);
    setData(Qt::UserRole + 4, 1);
}

EditLabelListItem::EditLabelListItem(const EditLabelListItem &item)
{
    d->m_view = item.d->m_view;
    d->m_values = item.d->m_values;
}

EditLabelListItem::~EditLabelListItem()
{
    d->m_view = NULL;
}


void EditLabelListItem::setData(int role, const QVariant &value)
{
    bool found = false;

    for(int i = 0; i < d->m_values.count(); ++i)
    {
        if(d->m_values.at(i).m_role == role)
        {
            d->m_values[i].m_value = value;
            found = true;
            break;
        }
    }

    if(!found)
        d->m_values.append(EditLabelLineItemData(role, value));

    if(d->m_view != NULL)
        d->m_view->d_ptr->m_model->itemChanged(this);
}

QVariant EditLabelListItem::data(int role) const
{
    for(int i = 0; i < d->m_values.count(); ++i)
    {
        if(d->m_values.at(i).m_role == role)
        {
            return d->m_values[i].m_value;
        }
    }

    return QVariant();
}

EditLabelListItem *EditLabelListItem::clone() const
{
   return new EditLabelListItem(*this);
}

EditLabelListItem &EditLabelListItem::operator=(const EditLabelListItem &item)
{
    if(this == &item)
        return *this;

    d->m_view = item.d->m_view;
    d->m_values = item.d->m_values;

    return *this;
}



EditLabelListItemPrivate::EditLabelListItemPrivate() :
    m_view(NULL)
{

}
