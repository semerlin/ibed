#include "editlabellistview.h"
#include "editlabellistmodel.h"
#include "editlabellistitem.h"

class EditLabelLineItemData
{
public:
    EditLabelLineItemData() :
        m_role(-1)
    {
    }

    EditLabelLineItemData(int role, const QVariant &value) :
        m_role(role),
        m_value(value)
    {
    }

    int m_role;
    QVariant m_value;

    bool operator==(const EditLabelLineItemData &data)
    {
        return ((m_role == data.m_role) && (m_value == data.m_value));
    }
};


class EditLabelListItemPrivate
{
public:
    EditLabelListItemPrivate(EditLabelListItem *item) :
        q(item)
    {
    }

    EditLabelListItem *q;
    QList<EditLabelLineItemData> m_values;
};

EditLabelListItem::EditLabelListItem() :
    m_view(NULL),
    d(new EditLabelListItemPrivate(this))
{
    int alignment = Qt::AlignVCenter | Qt::AlignLeft;
    setData(Qt::TextAlignmentRole, alignment);
    setData(Qt::UserRole + 2, 1);
    setData(Qt::UserRole + 3, 1);
    setData(Qt::UserRole + 4, 1);
}

EditLabelListItem::EditLabelListItem(const QString &name, const QString &text,
                                     const QString &extraName) :
    m_view(NULL),
    d(new EditLabelListItemPrivate(this))
{
    setData(Qt::UserRole, name);
    setData(Qt::DisplayRole, text);
    setData(Qt::UserRole + 1, extraName);
    int alignment = Qt::AlignVCenter | Qt::AlignLeft;
    setData(Qt::TextAlignmentRole, alignment);
    setData(Qt::UserRole + 2, 1);
    setData(Qt::UserRole + 3, 1);
    setData(Qt::UserRole + 4, 1);
}

EditLabelListItem::EditLabelListItem(const EditLabelListItem &item)
{
    d->m_values = item.d->m_values;
}

EditLabelListItem::~EditLabelListItem()
{
    m_view = NULL;
    delete d;
}


void EditLabelListItem::setData(int role, const QVariant &value)
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
        d->m_values.append(EditLabelLineItemData(role, value));

    if(m_view != NULL)
        m_view->m_model->itemChanged(this);
}

QVariant EditLabelListItem::data(int role) const
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

EditLabelListItem *EditLabelListItem::clone() const
{
   return new EditLabelListItem(*this);
}

EditLabelListItem &EditLabelListItem::operator=(const EditLabelListItem &item)
{
    if(this == &item)
        return *this;

    d->m_values = item.d->m_values;

    return *this;
}

