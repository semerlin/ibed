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
**  @file     iconbuttonbox.cpp
**  @brief    icon button box class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "iconbuttonbox.h"

class IconButtonBoxPrivate
{
public:
    QHash<QAbstractButton *, QList<QIcon> > m_icons;
};

IconButtonBox::IconButtonBox(QWidget *parent) :
    BaseButtonBox(parent),
    d_ptr(new IconButtonBoxPrivate)
{

}

IconButtonBox::IconButtonBox(Qt::Orientation orientation, QWidget *parent) :
    BaseButtonBox(orientation, parent),
    d_ptr(new IconButtonBoxPrivate)
{

}

IconButtonBox::~IconButtonBox()
{
    delete d_ptr;
}

bool IconButtonBox::addButtonIcon(const QString &name, const QIcon &icon)
{
    Q_D(IconButtonBox);
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        if(d->m_icons.contains(btn))
        {
            d->m_icons[btn].append(icon);
            return true;
        }
    }

    return false;
}


bool IconButtonBox::setButtonIcons(const QString &name, const QStringList &icons)
{
    Q_D(IconButtonBox);
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        if(d->m_icons.contains(btn))
        {
            d->m_icons[btn].clear();
        }

        foreach(const QString &name, icons)
        {
            d->m_icons[btn].append(QIcon(name));
        }

        if(d->m_icons[btn].count() > 0)
            btn->setIcon(d->m_icons[btn].at(0));

        return true;
    }

    return false;
}


bool IconButtonBox::setButtonIcons(int id, const QStringList &icons)
{
    Q_D(IconButtonBox);
    QAbstractButton *btn = button<QAbstractButton>(id);
    if(btn != NULL)
    {
        if(d->m_icons.contains(btn))
        {
            d->m_icons[btn].clear();
        }

        foreach(const QString &name, icons)
        {
            d->m_icons[btn].append(QIcon(name));
        }

        if(d->m_icons[btn].count() > 0)
            btn->setIcon(QIcon(icons.at(0)));

        return true;
    }

    return false;
}

bool IconButtonBox::setButtonIcons(const QString &name, const QList<QIcon> &icons)
{
    Q_D(IconButtonBox);
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        if(d->m_icons.contains(btn))
        {
            d->m_icons[btn].clear();
        }

        d->m_icons[btn] = icons;

        if(icons.count() > 0)
            btn->setIcon(icons.at(0));

        return true;
    }

    return false;
}

bool IconButtonBox::setButtonIcons(int id, const QList<QIcon> &icons)
{
    Q_D(IconButtonBox);
    QAbstractButton *btn = button<QAbstractButton>(id);
    if(btn != NULL)
    {
        if(d->m_icons.contains(btn))
        {
            d->m_icons[btn].clear();
        }

        d->m_icons[btn] = icons;

        if(icons.count() > 0)
            btn->setIcon(icons.at(0));

        return true;
    }

    return false;
}

void IconButtonBox::changeToIcon(const QString &name, int num)
{
    Q_D(IconButtonBox);
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        if(d->m_icons.contains(btn))
        {
            if(d->m_icons[btn].count() > num)
                btn->setIcon(d->m_icons[btn].at(num));
        }
    }
}

void IconButtonBox::changeToIcon(int id, int num)
{
    Q_D(IconButtonBox);
    QAbstractButton *btn = button<QAbstractButton>(id);
    if(btn != NULL)
    {
        if(d->m_icons.contains(btn))
        {
            if(d->m_icons[btn].count() > num)
                btn->setIcon(d->m_icons[btn].at(num));
        }
    }
}

void IconButtonBox::changeToIcon(const QString &name, const QIcon &icon)
{
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        btn->setIcon(icon);
    }
}

void IconButtonBox::changeToIcon(int id, const QIcon &icon)
{
    QAbstractButton *btn = button<QAbstractButton>(id);
    if(btn != NULL)
    {
        btn->setIcon(icon);
    }
}

void IconButtonBox::removeIcon(int id, int num)
{
    Q_D(IconButtonBox);
    QAbstractButton *btn = button<QAbstractButton>(id);
    if(btn != NULL)
    {
        if(d->m_icons.contains(btn))
        {
            if(d->m_icons[btn].count() > num)
                d->m_icons[btn].removeAt(num);
        }
    }
}

void IconButtonBox::removeIcon(const QString &name, int num)
{
    Q_D(IconButtonBox);
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        if(d->m_icons.contains(btn))
        {
            if(d->m_icons[btn].count() > num)
                d->m_icons[btn].removeAt(num);
        }
    }
}

void IconButtonBox::clearIcons()
{
    Q_D(IconButtonBox);
    d->m_icons.clear();
}
