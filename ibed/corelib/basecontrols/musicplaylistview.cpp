#include "musicplaylistitem.h"
#include "musicplaylistmodel.h"
#include "musicplaylistview.h"
#include "musicplaylistdelegate.h"





/**
 * @brief LineMusicPlayListView::LineMusicPlayListView
 * @param parent
 */
MusicPlayListView::MusicPlayListView(QWidget *parent) :
    QListView(parent),
    m_model(new MusicPlayListModel(this)),
    m_delegate(new MusicPlayListDelegate(this))
{
    setModel(m_model);
    setItemDelegate(m_delegate);
}

MusicPlayListView::~MusicPlayListView()
{
    if(m_model)
        delete m_model;

    if(m_delegate)
        delete m_delegate;
}

void MusicPlayListView::setDelegate(QStyledItemDelegate *delegate)
{
    if(delegate != NULL)
        setItemDelegate(delegate);
    else
        setItemDelegate(m_delegate);
}


void MusicPlayListView::addItem(MusicPlayListItem *item)
{
    item->m_view = this;
    m_model->insertRow(m_model->rowCount(), item);
}

void MusicPlayListView::insertItem(int row, MusicPlayListItem *item)
{
    item->m_view = this;
    m_model->insertRow(row, item);
}

void MusicPlayListView::clear()
{
    m_model->removeRows(0, m_model->rowCount());
}

MusicPlayListItem *MusicPlayListView::item(int row)
{
    return m_model->item(row);
}

void MusicPlayListView::setFont(const QFont &font)
{
    QList<MusicPlayListItem *> items = m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setFont(font);
    }
}

void MusicPlayListView::setSizeHint(const QSize &size)
{
    QList<MusicPlayListItem *> items = m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setSizeHint(size);
    }
}

void MusicPlayListView::setStrech(int name, int text, int extra)
{
    QList<MusicPlayListItem *> items = m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setStrech(name, text, extra);
    }
}
