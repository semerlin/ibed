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
**  @file     musicplaylistdelegate.cpp
**  @brief    music play list delegate class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "musicplaylistdelegate.h"
#include "musicplaylistmodel.h"
#include "musicplaylistitem.h"
#include "musicplaylistview.h"
#include <QStyledItemDelegate>
#include <QPainter>
#include <QLineEdit>
#include "formula.h"
#include <QPalette>


MusicPlayListDelegate::MusicPlayListDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}


void MusicPlayListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {
        MusicPlayListView *view = qobject_cast<MusicPlayListView *>(parent());
        MusicPlayListItem *item = view->model()->item(index);

        painter->save();

        int nameWidth = 0, iconWidth = 0, height = 0;
        calWidthAndHeight(option, index, nameWidth, iconWidth, height);

        QRect nameRect = QRect(option.rect.topLeft(), QSize(nameWidth - 5, height));
        QRect playIconRect = QRect(option.rect.topLeft() + QPoint(nameWidth, 0) , QSize(iconWidth - 5, height));
        QRect pauseIconRect = QRect(playIconRect.topLeft()  + QPoint(iconWidth, 0), QSize(iconWidth - 5, height));
        QRect stopIconRect = QRect(pauseIconRect.topLeft() + QPoint(iconWidth, 0) , QSize(iconWidth - 5, height));

        if(item->isSelected())
            painter->fillRect(option.rect, item->selectionBackground());

        painter->setFont(item->font());
        painter->drawText(nameRect, index.data(Qt::TextAlignmentRole).toInt(), item->name());

        QPixmap picPlay = QPixmap(item->playIcon());
        painter->drawPixmap(Formula::rectInRectPosition(picPlay.rect(), playIconRect, Qt::AlignCenter),
                            picPlay);

        QPixmap picPause = QPixmap(item->pauseIcon());
        painter->drawPixmap(Formula::rectInRectPosition(picPause.rect(), pauseIconRect, Qt::AlignCenter),
                            picPause);


        QPixmap picStop = QPixmap(item->stopIcon());
        painter->drawPixmap(Formula::rectInRectPosition(picStop.rect(), stopIconRect, Qt::AlignCenter),
                            picStop);


        painter->restore();
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

void MusicPlayListDelegate::calWidthAndHeight(const QStyleOptionViewItem &option, const QModelIndex &index,
                                              int &nameWidth, int &iconWidth, int &height) const
{
    int itemHeight = -1;
    int width = -1;
    MusicPlayListView *view = qobject_cast<MusicPlayListView *>(parent());
    MusicPlayListItem *item = view->model()->item(index);

    if(!index.data(Qt::SizeHintRole).isValid())
    {
        itemHeight = sizeHint(option, index).height();
        width = view->size().width();
    }
    else
    {
        QSize size = item->sizeHint();
        itemHeight = size.height();
        width = size.width();
    }

    if(itemHeight == -1)
        itemHeight = sizeHint(option, index).height();

    if(width == -1)
        width = view->size().width();

    int nameStrech = 0, iconStrech = 0;
    item->strech(nameStrech, iconStrech);
    if(nameStrech < 0)
        nameStrech = 0;

    if(iconStrech < 0)
        iconStrech = 0;

    int strechSum = nameStrech + iconStrech * 3;
    if(strechSum == 0)
    {
        nameStrech = 1;
        iconStrech = 1;
        strechSum = 4;
    }

    nameWidth = width / strechSum * nameStrech;
    iconWidth = width / strechSum * iconStrech;

    height = itemHeight;

}


QSize MusicPlayListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {
        if(!index.data(Qt::SizeHintRole).isValid())
            return QStyledItemDelegate::sizeHint(option, index);

        return index.data(Qt::SizeHintRole).toSize();
    }
    else
    {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}
