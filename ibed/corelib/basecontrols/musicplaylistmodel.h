#ifndef MUSICPLAYLISTMODEL_H
#define MUSICPLAYLISTMODEL_H

#include "basecontrols_global.h"
#include <QAbstractListModel>
#include <QStandardItemModel>

class MusicPlayListItem;
class MusicPlayListModelPrivate;

class BASECONTROLSSHARED_EXPORT MusicPlayListModel : public QAbstractListModel
{

public:
    explicit MusicPlayListModel(QObject *parent = 0);
    ~MusicPlayListModel();

public:
    void itemChanged(MusicPlayListItem *item);

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRow(int row, MusicPlayListItem *item);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    MusicPlayListItem *item(int row) const;
    MusicPlayListItem *item(const QModelIndex &index) const;
    QList<MusicPlayListItem *> allItems(void) const;

private:
    MusicPlayListModelPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(MusicPlayListModel)
};

#endif // MUSICPLAYLISTMODEL_H
