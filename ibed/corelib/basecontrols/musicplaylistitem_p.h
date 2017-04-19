#ifndef MUSICPLAYLISTITEM_P_H
#define MUSICPLAYLISTITEM_P_H

#include "basecontrols_global.h"
#include <QList>
#include <QVariant>

class MusicPlayListItem;
class MusicPlayListView;

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


class BASECONTROLSSHARED_EXPORT MusicPlayListItemPrivate
{
public:
    MusicPlayListView *m_view;
    QList<MusicPlayItemData> m_values;

};

#endif // MUSICPLAYLISTITEM_P

