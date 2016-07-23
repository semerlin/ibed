#include "editlabellistitem.h"
#include "editlabellistmodel.h"
#include "editlabellistview.h"
#include "editlabellistdelegate.h"





/**
 * @brief LineEditLabelListView::LineEditLabelListView
 * @param parent
 */
EditLabelListView::EditLabelListView(QWidget *parent) :
    QListView(parent),
    m_model(new EditLabelListModel(this)),
    m_delegate(new EditLabelListDelegate(this))
{
    setModel(m_model);
    setItemDelegate(m_delegate);
}

EditLabelListView::~EditLabelListView()
{
    if(m_model)
        delete m_model;

    if(m_delegate)
        delete m_delegate;
}

void EditLabelListView::setDelegate(QStyledItemDelegate *delegate)
{
    if(delegate != NULL)
        setItemDelegate(delegate);
    else
        setItemDelegate(m_delegate);
}


void EditLabelListView::addItem(EditLabelListItem *item)
{
    item->m_view = this;
    m_model->insertRow(m_model->rowCount(), item);
}

void EditLabelListView::insertItem(int row, EditLabelListItem *item)
{
    item->m_view = this;
    m_model->insertRow(row, item);
}

void EditLabelListView::clear()
{
    m_model->removeRows(0, m_model->rowCount());
}

EditLabelListItem *EditLabelListView::item(int row)
{
    return m_model->item(row);
}

void EditLabelListView::setFont(const QFont &font)
{
    QList<EditLabelListItem *> items = m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setFont(font);
    }
}

void EditLabelListView::setSizeHint(const QSize &size)
{
    QList<EditLabelListItem *> items = m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setSizeHint(size);
    }
}

void EditLabelListView::setStrech(int name, int text, int extra)
{
    QList<EditLabelListItem *> items = m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setStrech(name, text, extra);
    }
}
