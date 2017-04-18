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
**  @file     editlabellistview.cpp
**  @brief    edit label list view class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "editlabellistitem.h"
#include "editlabellistmodel.h"
#include "editlabellistview.h"
#include "editlabellistdelegate.h"
#include "boost/shared_ptr.hpp"
#include "editlabellistview_p.h"
#include "editlabellistitem_p.h"


/**
 * @brief LineEditLabelListView::LineEditLabelListView
 * @param parent
 */
EditLabelListView::EditLabelListView(QWidget *parent) :
    QListView(parent),
    d_ptr(new EditLabelListViewPrivate(this))
{
    setModel(d_ptr->m_model.get());
    setItemDelegate(d_ptr->m_delegate.get());
}

EditLabelListView::~EditLabelListView()
{
    delete d_ptr;
}

void EditLabelListView::setDelegate(QStyledItemDelegate *delegate)
{
    if(delegate != NULL)
        setItemDelegate(delegate);
    else
        setItemDelegate(d_ptr->m_delegate.get());
}


void EditLabelListView::addItem(EditLabelListItem *item)
{
    Q_D(EditLabelListView);
    item->d->m_view = this;
    d->m_model->insertRow(d->m_model->rowCount(), item);
}

void EditLabelListView::insertItem(int row, EditLabelListItem *item)
{
    item->d->m_view = this;
    d_ptr->m_model->insertRow(row, item);
}

void EditLabelListView::clear()
{
    Q_D(EditLabelListView);
    d->m_model->removeRows(0, d->m_model->rowCount());
}

QList<EditLabelListItem *> EditLabelListView::allItems() const
{
    return d_ptr->m_model->allItems();
}

EditLabelListItem *EditLabelListView::item(int row) const
{
    return d_ptr->m_model->item(row);
}

void EditLabelListView::setFont(const QFont &font)
{
    QList<EditLabelListItem *> items = d_ptr->m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setFont(font);
    }
}

void EditLabelListView::setSizeHint(const QSize &size)
{
    QList<EditLabelListItem *> items = d_ptr->m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setSizeHint(size);
    }
}

void EditLabelListView::setStrech(int name, int text, int extra)
{
    QList<EditLabelListItem *> items = d_ptr->m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setStrech(name, text, extra);
    }
}


EditLabelListViewPrivate::EditLabelListViewPrivate(EditLabelListView *parent) :
    m_model(new EditLabelListModel(parent)),
    m_delegate(new EditLabelListDelegate(parent)),
    q_ptr(parent)
{

}
