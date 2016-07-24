#ifndef MUSICPLAYLISTVIEW_H
#define MUSICPLAYLISTVIEW_H

#include "basecontrols_global.h"
#include <QListView>
#include <QStyledItemDelegate>

class MusicPlayListItem;
class MusicPlayListDelegate;
class MusicPlayListModel;

class BASECONTROLSSHARED_EXPORT MusicPlayListView : public QListView
{
    Q_OBJECT
    friend class MusicPlayListItem;
    friend class MusicPlayListDelegate;

public:
    MusicPlayListView(QWidget *parent = 0);
    ~MusicPlayListView();

public:
    void addItem(MusicPlayListItem *item);
    void insertItem(int row, MusicPlayListItem *item);
    void clear(void);
    MusicPlayListItem *item(int row);
    void setFont(const QFont &font);
    void setSizeHint(const QSize &size);
    void setStrech(int name, int icon);

signals:
    void itemClicked(MusicPlayListItem *item);

private slots:
    void onClicked(const QModelIndex &index);

private:
    MusicPlayListModel *m_model;
    MusicPlayListDelegate *m_delegate;
};

#endif // MusicPlayListView_H
