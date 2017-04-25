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
**  @file     musicplaylistitem.cpp
**  @brief    music play list item class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "musicplaylistview.h"
#include "musicplaylistmodel.h"
#include "musicplaylistitem.h"
#include "musicplaylistitem_p.h"

MusicPlayListItem::MusicPlayListItem() :
    d(new MusicPlayListItemPrivate)
{
    int alignment = Qt::AlignVCenter | Qt::AlignLeft;
    setData(Qt::TextAlignmentRole, alignment);
    setData(Qt::UserRole + 3, 1);
    setData(Qt::UserRole + 4, 1);
    setData(Qt::UserRole + 5, QColor(0, 96, 169));
    setData(Qt::UserRole + 6, false);
}


MusicPlayListItem::MusicPlayListItem(const QString &name, const QString &iconPlay,
                                     const QString &iconPause, const QString &iconStop) :
    d(new MusicPlayListItemPrivate)
{
    setData(Qt::DisplayRole, name);
    setData(Qt::UserRole, iconPlay);
    setData(Qt::UserRole + 1, iconPause);
    setData(Qt::UserRole + 2, iconStop);
    int alignment = Qt::AlignVCenter | Qt::AlignLeft;
    setData(Qt::TextAlignmentRole, alignment);
    setData(Qt::UserRole + 3, 1);
    setData(Qt::UserRole + 4, 1);
    setData(Qt::UserRole + 5, QColor(0, 96, 169));
    setData(Qt::UserRole + 6, false);
}

MusicPlayListItem::MusicPlayListItem(const MusicPlayListItem &item)
{
    d->m_view = item.d->m_view;
    d->m_values = item.d->m_values;
}

MusicPlayListItem::~MusicPlayListItem()
{
    d->m_view = NULL;
}


void MusicPlayListItem::setData(int role, const QVariant &value)
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
        d->m_values.append(MusicPlayItemData(role, value));

    if(d->m_view != NULL)
        d->m_view->model()->itemChanged(this);
}

QVariant MusicPlayListItem::data(int role) const
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

MusicPlayListItem *MusicPlayListItem::clone() const
{
    return new MusicPlayListItem(*this);
}


MusicPlayListItem &MusicPlayListItem::operator=(const MusicPlayListItem &item)
{
    if(this == &item)
        return *this;

    d->m_values = item.d->m_values;

    return *this;
}



MusicPlayListItemPrivate::MusicPlayListItemPrivate() :
    m_view(NULL)
{

}
