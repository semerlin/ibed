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
**  @file     iconpushbutton.cpp
**  @brief    icon pushbutton class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "iconpushbutton.h"

class IconPushButtonPrivate
{
public:
    QList<QIcon> m_icons;
};

IconPushButton::IconPushButton(QWidget *parent) :
    QPushButton(parent),
    d_ptr(new IconPushButtonPrivate)
{

}

IconPushButton::~IconPushButton()
{
    delete d_ptr;
}

void IconPushButton::addIcon(const QIcon &icon)
{
    d_ptr->m_icons.append(icon);
}

void IconPushButton::addIcon(const QString &icon)
{
    d_ptr->m_icons.append(QIcon(icon));
}

void IconPushButton::setIcons(const QList<QIcon> &icons)
{
    Q_D(IconPushButton);
    d->m_icons.clear();
    d->m_icons = icons;
    if(d->m_icons.count() > 0)
        setIcon(d->m_icons.at(0));
}

void IconPushButton::setIcons(const QStringList &icons)
{
    Q_D(IconPushButton);
    d->m_icons.clear();
    foreach(const QString &name, icons)
        d->m_icons.append(QIcon(name));

    if(d->m_icons.count() > 0)
        setIcon(d->m_icons.at(0));
}

void IconPushButton::changeToIcon(int id)
{
    Q_D(IconPushButton);
    Q_ASSERT(d->m_icons.count() > id);
    setIcon(d->m_icons[id]);
}

void IconPushButton::removeIcon(int id)
{
    Q_D(IconPushButton);
    Q_ASSERT(d->m_icons.count() > id);
    d->m_icons.removeAt(id);
}

void IconPushButton::clearIcons()
{
    d_ptr->m_icons.clear();
}
