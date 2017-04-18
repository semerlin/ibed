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
**  @file     editlabellistdelegate.cpp
**  @brief    edit label list delegate class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "editlabellistdelegate.h"
#include "editlabellistitem.h"
#include "editlabellistmodel.h"
#include "editlabellistview.h"
#include <QStyledItemDelegate>
#include <QPainter>
#include <QLineEdit>
#include "editlabellistview_p.h"


EditLabelListDelegate::EditLabelListDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}


void EditLabelListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {
        EditLabelListView *view = qobject_cast<EditLabelListView *>(parent());
        EditLabelListItem *item = view->d_ptr->m_model->item(index);

        painter->save();

        int nameWidth = 0, textWidth = 0, extraWidth = 0, height = 0;
        calWidthAndHeight(option, index, nameWidth, textWidth, extraWidth, height);

        QRect nameRect = QRect(option.rect.topLeft(), QSize(nameWidth - 5, height));
        QRect textRect = QRect(option.rect.topLeft() + QPoint(nameWidth, 0) , QSize(textWidth - 5, height));
        QRect extraRect = QRect(option.rect.topLeft() + QPoint(nameWidth + textWidth, 0) , QSize(extraWidth - 5, height));

        painter->setFont(item->font());
        painter->drawText(nameRect, item->textAlignment(), item->name());
        painter->drawText(textRect, item->textAlignment(), item->text());
        painter->drawText(extraRect, item->textAlignment(), item->extraName());

        painter->restore();
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QWidget *EditLabelListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void EditLabelListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if(lineEdit)
    {
        lineEdit->setText(index.data(Qt::DisplayRole).toString());
    }
}

void EditLabelListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if(lineEdit)
    {
        model->setData(index, lineEdit->text(), Qt::EditRole);
    }
}

void EditLabelListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int nameWidth = 0, textWidth = 0, extraWidth = 0, height = 0;
    calWidthAndHeight(option, index, nameWidth, textWidth, extraWidth, height);

    QFont font = index.data(Qt::FontRole).value<QFont>();
    int fontHeight = QFontMetrics(font).height();

    //calucate verical offet
    int offset = 0;
    int alignment = index.data(Qt::TextAlignmentRole).toInt();
    if(alignment & Qt::AlignBottom)
    {
        offset = height - fontHeight;
    }
    else if(alignment & Qt::AlignVCenter)
    {
        offset = (height - fontHeight) / 2;
    }

    QRect decorationRect = QRect(option.rect.topLeft() + QPoint(nameWidth, offset-4), QSize(textWidth, fontHeight+8));
    editor->setGeometry(decorationRect);
    editor->setFont(font);
}

void EditLabelListDelegate::calWidthAndHeight(const QStyleOptionViewItem &option, const QModelIndex &index,
                                              int &nameWidth, int &textWidth, int &extraWidth, int &height) const
{
    int itemHeight = -1;
    int width = -1;
    EditLabelListView *view = qobject_cast<EditLabelListView *>(parent());
    EditLabelListItem *item = view->d_ptr->m_model->item(index);

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

    int nameStrech = 0, textStrech = 0, extraStrech = 0;
    item->strech(nameStrech, textStrech, extraStrech);
    if(nameStrech < 0)
        nameStrech = 0;

    if(textStrech < 0)
        textStrech = 0;

    if(extraStrech < 0)
        extraStrech = 0;

    int strechSum = nameStrech + textStrech + extraStrech;
    if(strechSum == 0)
    {
        nameStrech = 1;
        textStrech = 1;
        extraStrech = 1;
        strechSum = 3;
    }

    nameWidth = width / strechSum * nameStrech;
    textWidth = width / strechSum * textStrech;
    extraWidth = width / strechSum * extraStrech;

    height = itemHeight;

}


QSize EditLabelListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
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
