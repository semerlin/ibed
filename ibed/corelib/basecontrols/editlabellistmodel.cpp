#include "editlabellistitem.h"
#include "editlabellistview.h"
#include "editlabellistmodel.h"

EditLabelListModel::EditLabelListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

EditLabelListModel::~EditLabelListModel()
{
    while(m_items.count())
        delete m_items.takeAt(0);
}


void EditLabelListModel::itemChanged(EditLabelListItem *item)
{
    int itemIndex = m_items.indexOf(item);
    if(itemIndex >= 0)
        emit dataChanged(index(itemIndex), index(itemIndex));
}


int EditLabelListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_items.count();
}

QVariant EditLabelListModel::data(const QModelIndex &index, int role) const
{
    if((!index.isValid()) && (index.row() >= m_items.count()))
        return QVariant();

    return m_items.at(index.row())->data(role);
}

bool EditLabelListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if((!index.isValid()) && (index.row() >= m_items.count()))
        return false;


    m_items.at(index.row())->setData(role, value);
    if(role == Qt::EditRole)
    {
        m_items.at(index.row())->setData(Qt::DisplayRole, value);
    }

    return true;
}

Qt::ItemFlags EditLabelListModel::flags(const QModelIndex &index) const
{
    if((!index.isValid()) && (index.row() >= m_items.count()))
        return 0;

    return (Qt::ItemIsEditable | Qt::ItemIsEnabled);
}

bool EditLabelListModel::insertRow(int row, EditLabelListItem *item)
{
    beginInsertRows(QModelIndex(), row, row);

    m_items.insert(row, item);

    endInsertRows();

    return true;
}

bool EditLabelListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    for(int pos = row; pos < (row + count); ++pos)
    {
        m_items.insert(pos, new EditLabelListItem());
    }
    endInsertRows();
    return true;
}

bool EditLabelListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    EditLabelListItem *item = NULL;
    beginRemoveRows(parent, row, row + count - 1);

    while(count--)
    {
        item = m_items.takeAt(row);
        if(item != NULL)
            delete item;
    }

    endRemoveRows();
    return true;
}

EditLabelListItem *EditLabelListModel::item(int row) const
{
    if(row < m_items.count())
        return m_items.at(row);

    return NULL;
}

EditLabelListItem *EditLabelListModel::item(const QModelIndex &index) const
{
    if(index.row() < m_items.count())
        return m_items.at(index.row());

    return NULL;
}

QList<EditLabelListItem *> EditLabelListModel::allItems() const
{
    return m_items;
}
