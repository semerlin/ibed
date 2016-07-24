#ifndef MUSICPLAYLISTDELEGATE_H
#define MUSICPLAYLISTDELEGATE_H

#include <QStyledItemDelegate>
#include "basecontrols_global.h"

class BASECONTROLSSHARED_EXPORT MusicPlayListDelegate : public QStyledItemDelegate
{
public:
    explicit MusicPlayListDelegate(QObject *parent = 0);

public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

protected:
    void calWidthAndHeight(const QStyleOptionViewItem &option, const QModelIndex &index,
                           int &nameWidth, int &iconWidth, int &height) const;
};

#endif // MUSICPLAYLISTDELEGATE_H
