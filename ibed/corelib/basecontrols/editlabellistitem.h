#ifndef EDITLABELLISTITEM_H
#define EDITLABELLISTITEM_H

#include "basecontrols_global.h"
#include <QFont>
#include <QSize>
#include <QVariant>
#include "boost/shared_ptr.hpp"

class EditLabelListView;
class EditLabelListItemPrivate;

class BASECONTROLSSHARED_EXPORT EditLabelListItem
{
public:
    explicit EditLabelListItem();
    explicit EditLabelListItem(const QString &name, const QString &text,
                               const QString &extraName);
    EditLabelListItem(const EditLabelListItem &item);

    ~EditLabelListItem();

public:
    void setData(int role, const QVariant &value);
    QVariant data(int role) const;
    EditLabelListItem *clone(void) const;

public:
    inline void setName(const QString &name)
    {
        setData(Qt::UserRole, name);
    }

    inline void setText(const QString &text)
    {
        setData(Qt::DisplayRole, text);
    }

    inline void setExtraName(const QString &extra)
    {
        setData(Qt::UserRole + 1, extra);
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

    inline void setStrech(int name, int text, int extra)
    {
        setData(Qt::UserRole + 2, name);
        setData(Qt::UserRole + 3, text);
        setData(Qt::UserRole + 4, extra);
    }

    inline QSize sizeHint(void) const
    {
        return data(Qt::SizeHintRole).toSize();
    }


    inline QFont font(void) const
    {
        return data(Qt::FontRole).value<QFont>();
    }

    inline QString text(void) const
    {
        return data(Qt::DisplayRole).toString();
    }

    inline QString name(void) const
    {
        return data(Qt::UserRole).toString();
    }

    inline QString extraName(void) const
    {
        return data(Qt::UserRole + 1).toString();
    }

    inline int textAlignment(void) const
    {
        return data(Qt::TextAlignmentRole).toInt();
    }

    inline void strech(int &name, int &text, int &extra)
    {
        name = data(Qt::UserRole + 2).toInt();
        text = data(Qt::UserRole + 3).toInt();
        extra = data(Qt::UserRole + 4).toInt();
    }

    EditLabelListItem& operator=(const EditLabelListItem &item);

private:
    friend class EditLabelListView;
    boost::shared_ptr<EditLabelListItemPrivate> d;
};

#endif // EditLabelListItem_H
