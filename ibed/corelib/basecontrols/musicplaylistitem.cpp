#include "musicplaylistview.h"
#include "musicplaylistmodel.h"
#include "musicplaylistitem.h"

class MusicPlayItemData
{
public:
    MusicPlayItemData() :
        m_role(-1)
    {
    }

    MusicPlayItemData(int role, const QVariant &value) :
        m_role(role),
        m_value(value)
    {
    }

    int m_role;
    QVariant m_value;

    bool operator==(const MusicPlayItemData &data)
    {
        return ((m_role == data.m_role) && (m_value == data.m_value));
    }
};


class MusicPlayListItemPrivate
{
public:
    MusicPlayListItemPrivate(MusicPlayListItem *item) :
        q(item)
    {
    }

    MusicPlayListItem *q;
    QList<MusicPlayItemData> m_values;
};

MusicPlayListItem::MusicPlayListItem() :
    m_view(NULL),
    d(new MusicPlayListItemPrivate(this))
{
    int alignment = Qt::AlignVCenter | Qt::AlignLeft;
    setData(Qt::TextAlignmentRole, alignment);
    setData(Qt::UserRole + 3, 1);
    setData(Qt::UserRole + 4, 1);
    setData(Qt::UserRole + 5, QColor(0, 96, 169));
    setData(Qt::UserRole + 6, false);
}


MusicPlayListItem::MusicPlayListItem(const QString &name, const QString &iconPlay,
                                     const QString &iconPause, const QString &iconStop) :
    m_view(NULL),
    d(new MusicPlayListItemPrivate(this))
{
    setData(Qt::DisplayRole, name);
    setData(Qt::UserRole, iconPlay);
    setData(Qt::UserRole + 1, iconPause);
    setData(Qt::UserRole + 2, iconStop);
    int alignment = Qt::AlignVCenter | Qt::AlignLeft;
    setData(Qt::TextAlignmentRole, alignment);
    setData(Qt::UserRole + 3, 1);
    setData(Qt::UserRole + 4, 1);
    setData(Qt::UserRole + 5, QColor(0, 96, 169));
    setData(Qt::UserRole + 6, false);
}

MusicPlayListItem::MusicPlayListItem(const MusicPlayListItem &item)
{
    d->m_values = item.d->m_values;
}

MusicPlayListItem::~MusicPlayListItem()
{
    m_view = NULL;
    delete d;
}


void MusicPlayListItem::setData(int role, const QVariant &value)
{
    bool found = false;

    for(int i = 0; i < d->m_values.count(); ++i)
    {
        if(d->m_values.at(i).m_role == role)
        {
            d->m_values[i].m_value = value;
            found = true;
            break;
        }
    }

    if(!found)
        d->m_values.append(MusicPlayItemData(role, value));

    if(m_view != NULL)
        m_view->model()->itemChanged(this);
}

QVariant MusicPlayListItem::data(int role) const
{
    for(int i = 0; i < d->m_values.count(); ++i)
    {
        if(d->m_values.at(i).m_role == role)
        {
            return d->m_values[i].m_value;
        }
    }

    return QVariant();
}

MusicPlayListItem *MusicPlayListItem::clone() const
{
    return new MusicPlayListItem(*this);
}


MusicPlayListItem &MusicPlayListItem::operator=(const MusicPlayListItem &item)
{
    if(this == &item)
        return *this;

    d->m_values = item.d->m_values;

    return *this;
}

