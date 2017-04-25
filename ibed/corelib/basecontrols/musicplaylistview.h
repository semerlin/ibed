#ifndef MUSICPLAYLISTVIEW_H
#define MUSICPLAYLISTVIEW_H

#include "basecontrols_global.h"
#include <QListView>
#include <QStyledItemDelegate>
#include "boost/shared_ptr.hpp"

class MusicPlayListItem;
class MusicPlayListDelegate;
class MusicPlayListModel;
class MusicPlayListViewPrivate;

class BASECONTROLSSHARED_EXPORT MusicPlayListView : public QListView
{
    Q_OBJECT
public:
    MusicPlayListView(QWidget *parent = 0);
    ~MusicPlayListView();

public:
    MusicPlayListModel *model(void) const;
    void addItem(MusicPlayListItem *item);
    void insertItem(int row, MusicPlayListItem *item);
    void clear(void);
    MusicPlayListItem *item(int row);
    void setFont(const QFont &font);
    void setSizeHint(const QSize &size);
    void setStrech(int name, int icon);
    void setSelectionBackground(const QBrush &brush);

signals:
    void itemClicked(MusicPlayListItem *item);
    void currentItemChanged(MusicPlayListItem *current, MusicPlayListItem *previous);
    void iconClicked(MusicPlayListItem *item, int index);

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void onClicked(const QModelIndex &index);

private:
    friend class MusicPlayListItem;
    friend class MusicPlayListDelegate;
    boost::shared_ptr<MusicPlayListViewPrivate> d;
//    MusicPlayListViewPrivate *d;
};

#endif // MusicPlayListView_H
