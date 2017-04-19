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
**  @file     linetableview.cpp
**  @brief    line table view class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "linetableview.h"
#include <QTableWidget>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QHeaderView>

class LineDelegate : public QStyledItemDelegate
{
public:
    LineDelegate(int orientation, QTableView *tableView);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QPen m_pen;
    QTableView *m_view;
    int m_orientation;
};

LineDelegate::LineDelegate(int orientation, QTableView *tableView) :
    m_view(tableView),
    m_orientation(orientation)
{
    int gridHint = tableView->style()->styleHint(QStyle::SH_Table_GridLineColor, new QStyleOptionViewItemV4());

    //get gridline pen color
    QColor gridColor = static_cast<QRgb>(gridHint);
    m_pen = QPen(gridColor, 0, tableView->gridStyle());
}

void LineDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index)const
{
    QStyledItemDelegate::paint(painter, option, index);

    QPen oldPen = painter->pen();

    painter->setPen(m_pen);

    if(m_orientation & Qt::Vertical)
    {
        painter->drawLine(option.rect.topLeft(), option.rect.bottomLeft());
    }

    if(m_orientation & Qt::Horizontal)
    {
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    }

    painter->setPen(oldPen);
}


LineTableView::LineTableView(QWidget *parent) :
    QTableView(parent)
{
    setShowGrid(false);
    setItemDelegate(new LineDelegate(Qt::Vertical | Qt::Horizontal, this));
}

LineTableView::LineTableView(Qt::Orientation orientation, QWidget *parent) :
    QTableView(parent)
{
    setShowGrid(false);
    setItemDelegate(new LineDelegate(orientation, this));
}
