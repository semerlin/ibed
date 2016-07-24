#include "musicplaylistitem.h"
#include "musicplaylistmodel.h"
#include "musicplaylistview.h"
#include "musicplaylistdelegate.h"
#include <QMouseEvent>
#include <QPoint>


class MusicPlayListViewPrivate
{
public:
    MusicPlayListViewPrivate(MusicPlayListView *view) :
        m_view(view)
    {
        m_model = new MusicPlayListModel(view);
        m_delegate = new MusicPlayListDelegate(view);
    }

    ~MusicPlayListViewPrivate()
    {
        delete m_model;
        delete m_delegate;
    }

public:
    MusicPlayListModel *m_model;
    MusicPlayListDelegate *m_delegate;
    MusicPlayListItem *m_prevItem;
    MusicPlayListItem *m_currentItem;

private:
    MusicPlayListView *m_view;
};



/**
 * @brief LineMusicPlayListView::LineMusicPlayListView
 * @param parent
 */
MusicPlayListView::MusicPlayListView(QWidget *parent) :
    QListView(parent),
    d(new MusicPlayListViewPrivate(this))
{
    d->m_prevItem = NULL;
    d->m_currentItem = NULL;
    setModel(d->m_model);
    setItemDelegate(d->m_delegate);
    connect(this, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onClicked(const QModelIndex&)));

}

MusicPlayListView::~MusicPlayListView()
{
    delete d;
}

MusicPlayListModel *MusicPlayListView::model() const
{
   return d->m_model;
}


void MusicPlayListView::addItem(MusicPlayListItem *item)
{
    item->m_view = this;
    d->m_model->insertRow(d->m_model->rowCount(), item);
}

void MusicPlayListView::insertItem(int row, MusicPlayListItem *item)
{
    item->m_view = this;
    d->m_model->insertRow(row, item);
}

void MusicPlayListView::clear()
{
    d->m_model->removeRows(0, d->m_model->rowCount());
}

MusicPlayListItem *MusicPlayListView::item(int row)
{
    return d->m_model->item(row);
}

void MusicPlayListView::setFont(const QFont &font)
{
    QList<MusicPlayListItem *> items = d->m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setFont(font);
    }
}

void MusicPlayListView::setSizeHint(const QSize &size)
{
    QList<MusicPlayListItem *> items = d->m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setSizeHint(size);
    }
}

void MusicPlayListView::setStrech(int name, int icon)
{
    QList<MusicPlayListItem *> items = d->m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setStrech(name, icon);
    }
}

void MusicPlayListView::setSelectionBackground(const QBrush &brush)
{
    QList<MusicPlayListItem *> items = d->m_model->allItems();
    for(int i = 0; i < items.count(); ++i)
    {
        items.at(i)->setSelectionBackground(brush);
    }
}

void MusicPlayListView::onClicked(const QModelIndex &index)
{
    d->m_prevItem = d->m_currentItem;
    d->m_currentItem = d->m_model->item(index);
    emit itemClicked(d->m_model->item(index));
    emit currentItemChanged(d->m_currentItem, d->m_prevItem);
}

void MusicPlayListView::mousePressEvent(QMouseEvent *event)
{
    QListView::mousePressEvent(event);
    int x = event->x();

    int width = 0, nameStrech, iconStrech, playIconStart, pauseIconStart, stopIconStart, stopPos;
    if(d->m_currentItem != NULL)
    {
        if(!d->m_currentItem->data(Qt::SizeHintRole).isValid())
        {
            width = this->width();
        }
        else
        {
            width = d->m_currentItem->sizeHint().width();
            if(width < 0)
                width = this->width();
        }

        d->m_currentItem->strech(nameStrech, iconStrech);
        if(nameStrech < 0)
            nameStrech = 0;

        if(iconStrech < 0)
            iconStrech = 0;

        int sumStrech = nameStrech + iconStrech * 3;
        if(sumStrech == 0)
        {
            nameStrech = 1;
            iconStrech = 1;
            sumStrech = 4;
        }

        playIconStart = width / sumStrech * nameStrech;
        pauseIconStart = playIconStart + width / sumStrech * iconStrech;
        stopIconStart = pauseIconStart + width / sumStrech * iconStrech;
        stopPos = stopIconStart + width / sumStrech * iconStrech;

        if((x >= playIconStart) && (x < pauseIconStart))
        {
            emit iconClicked(d->m_currentItem, 0);
        }
        else if((x >= pauseIconStart) && (x < stopIconStart))
        {
            emit iconClicked(d->m_currentItem, 1);
        }
        else if((x >= stopIconStart) && (x < stopPos))
        {
            emit iconClicked(d->m_currentItem, 2);
        }

    }
}
