#ifndef EDITLABELLISTITEM_P_H
#define EDITLABELLISTITEM_P_H

#include <QVariant>

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


class EditLabelListView;

class EditLabelListItemPrivate
{
public:
    EditLabelListItemPrivate();

public:
    EditLabelListView *m_view;
    QList<EditLabelLineItemData> m_values;
};



#endif // EDITLABELLISTITEM_P

