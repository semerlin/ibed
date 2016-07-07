#include <QWidget>
#include <QVariant>
#include "util.h"
#include <QString>
#include <QStyle>


QString Util::fileName(const QString &name)
{
    int dot = name.lastIndexOf('.');
    if(dot != -1)
        return name.left(dot);
    else
        return name;
}

QString Util::fileSuffix(const QString &name)
{
    int dot = name.lastIndexOf('.');
    if(dot != -1)
        return name.right(dot);
    else
        return QString("");
}

void Util::changeQssWidgetProperty(QWidget *widget, const QString &property, const QVariant &val)
{
    widget->setProperty(property.toAscii().data(), val);
    refreshWidget(widget);
}

void Util::refreshWidget(QWidget *widget)
{
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
    widget->update();
}

Util::Util()
{
}

