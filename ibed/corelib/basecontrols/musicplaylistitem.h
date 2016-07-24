#ifndef MUSICPLAYLISTITEM_H
#define MUSCIPLAYLISTITEM_H

#include "basecontrols_global.h"
#include <QFont>
#include <QSize>
#include <QVariant>

class MusicPlayListView;
class MusicPlayListItemPrivate;

class BASECONTROLSSHARED_EXPORT MusicPlayListItem
{
    friend class MusicPlayListView;

public:
    explicit MusicPlayListItem();
    explicit MusicPlayListItem(const QString &name, const QString &iconPlay,
                               const QString &iconPause, const QString &iconStop);
    MusicPlayListItem(const MusicPlayListItem &item);

    ~MusicPlayListItem();

public:
    void setData(int role, const QVariant &value);
    QVariant data(int role) const;
    MusicPlayListItem *clone(void) const;

public:
    inline void setName(const QString &name)
    {
        setData(Qt::DisplayRole, name);
    }

    inline void setPlayIcon(const QString &icon)
    {
        setData(Qt::UserRole, icon);
    }

    inline void setPauseIcon(const QString &icon)
    {
        setData(Qt::UserRole + 1, icon);
    }

    inline void setStopIcon(const QString &icon)
    {
        setData(Qt::UserRole + 2, icon);
    }

    inline void setSizeHint(const QSize &size)
    {
        setData(Qt::SizeHintRole, size);
    }

    inline void setFont(const QFont &font)
    {
        setData(Qt::FontRole, font);
    }

    inline void setTextAlignment(int alignment)
    {
        setData(Qt::TextAlignmentRole, alignment);
    }

    inline void setStrech(int name, int icon)
    {
        setData(Qt::UserRole + 3, name);
        setData(Qt::UserRole + 4, icon);
    }

    inline QSize sizeHint(void) const
    {
        return data(Qt::SizeHintRole).toSize();
    }


    inline QFont font(void) const
    {
        return data(Qt::SizeHintRole).value<QFont>();
    }

    inline QString name(void) const
    {
        return data(Qt::DisplayRole).toString();
    }

    inline int textAlignment(void) const
    {
        return data(Qt::TextAlignmentRole).toInt();
    }


    MusicPlayListItem& operator=(const MusicPlayListItem &item);

private:
    MusicPlayListView *m_view;
    MusicPlayListItemPrivate *d;
};

#endif // MUSICLISTPLAYITEM_H
