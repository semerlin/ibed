#ifndef EDITLABELLISTMODEL_H
#define EDITLABELLISTMODEL_H

#include "basecontrols_global.h"
#include <QAbstractListModel>
#include <QStandardItemModel>

class EditLabelListItem;
class EditLabelListModelPrivate;

class BASECONTROLSSHARED_EXPORT EditLabelListModel : public QAbstractListModel
{

public:
    explicit EditLabelListModel(QObject *parent = 0);
    ~EditLabelListModel();

public:
    void itemChanged(EditLabelListItem *item);

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRow(int row, EditLabelListItem *item);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    EditLabelListItem *item(int row) const;
    EditLabelListItem *item(const QModelIndex &index) const;
    QList<EditLabelListItem *> allItems(void) const;

private:
    EditLabelListModelPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(EditLabelListModel)
};

#endif // EDITLABELLISTMODEL_H
