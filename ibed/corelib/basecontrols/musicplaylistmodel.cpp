#include "musicplaylistitem.h"
#include "musicplaylistview.h"
#include "musicplaylistmodel.h"

MusicPlayListModel::MusicPlayListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

MusicPlayListModel::~MusicPlayListModel()
{
    while(m_items.count())
        delete m_items.takeAt(0);
}


void MusicPlayListModel::itemChanged(MusicPlayListItem *item)
{
    int itemIndex = m_items.indexOf(item);
    if(itemIndex >= 0)
        emit dataChanged(index(itemIndex), index(itemIndex));
}


int MusicPlayListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_items.count();
}

QVariant MusicPlayListModel::data(const QModelIndex &index, int role) const
{
    if((!index.isValid()) && (index.row() >= m_items.count()))
        return QVariant();

    return m_items.at(index.row())->data(role);
}

bool MusicPlayListModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

Qt::ItemFlags MusicPlayListModel::flags(const QModelIndex &index) const
{
    if((!index.isValid()) && (index.row() >= m_items.count()))
        return 0;

    return (Qt::ItemIsEditable | Qt::ItemIsEnabled);
}

bool MusicPlayListModel::insertRow(int row, MusicPlayListItem *item)
{
    beginInsertRows(QModelIndex(), row, row);

    m_items.insert(row, item);

    endInsertRows();

    return true;
}

bool MusicPlayListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    for(int pos = row; pos < (row + count); ++pos)
    {
        m_items.insert(pos, new MusicPlayListItem());
    }
    endInsertRows();
    return true;
}

bool MusicPlayListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    MusicPlayListItem *item = NULL;
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

MusicPlayListItem *MusicPlayListModel::item(int row) const
{
    if(row < m_items.count())
        return m_items.at(row);

    return NULL;
}

MusicPlayListItem *MusicPlayListModel::item(const QModelIndex &index) const
{
    if(index.row() < m_items.count())
        return m_items.at(index.row());

    return NULL;
}

QList<MusicPlayListItem *> MusicPlayListModel::allItems() const
{
    return m_items;
}
