#include "musicplaylistdelegate.h"
#include "musicplaylistmodel.h"
#include "musicplaylistitem.h"
#include "musicplaylistview.h"
#include <QStyledItemDelegate>
#include <QPainter>
#include <QLineEdit>
#include "formula.h"


MusicPlayListDelegate::MusicPlayListDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}


void MusicPlayListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {

        MusicPlayListView *view = qobject_cast<MusicPlayListView *>(parent());
        MusicPlayListItem *item = view->m_model->item(index);
        painter->save();

        int nameWidth = 0, iconWidth = 0, height = 0;
        calWidthAndHeight(option, index, nameWidth, iconWidth, height);

        QRect nameRect = QRect(option.rect.topLeft(), QSize(nameWidth - 5, height));
        QRect playIconRect = QRect(option.rect.topLeft() + QPoint(nameWidth, 0) , QSize(iconWidth - 5, height));
        QRect pauseIconRect = QRect(playIconRect.topLeft()  + QPoint(iconWidth, 0), QSize(iconWidth - 5, height));
        QRect stopIconRect = QRect(pauseIconRect.topLeft() + QPoint(iconWidth, 0) , QSize(iconWidth - 5, height));

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
    MusicPlayListItem *item = view->m_model->item(index);

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
