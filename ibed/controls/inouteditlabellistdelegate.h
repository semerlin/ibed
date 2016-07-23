#ifndef INOUTEDITLABELLISTDELEGATE_H
#define INOUTEDITLABELLISTDELEGATE_H

#include "controls_global.h"
#include "editlabellistdelegate.h"

class CONTROLSSHARED_EXPORT InoutEditLabelListDelegate : public EditLabelListDelegate
{
public:
    InoutEditLabelListDelegate(QObject *parent = 0);

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // INOUTEDITLABELLISTDELEGATE_H
