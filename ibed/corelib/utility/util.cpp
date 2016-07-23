#include <QStringList>
#include <QWidget>
#include <QVariant>
#include "util.h"
#include <QString>
#include <QStyle>
#include <QDebug>


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

QColor Util::stringListToColor(const QStringList &color)
{
    int retVal[3] = {0, 0, 0};
    for(int i = 0; i < color.count(); ++i)
    {
        retVal[i] = color.at(i).toInt();
        if(i >= 2)
            break;
    }

    return QColor(retVal[0], retVal[1], retVal[2]);

}

QStringList Util::colorToStringList(const QColor &color)
{
    return QStringList() << QString::number(color.red())
                         << QString::number(color.green())
                         << QString::number(color.blue());
}

Util::Util()
{
}

