#ifndef UTIL_H
#define UTIL_H

#include "utility_global.h"

class QWidget;
class QVariant;
class QStringList;
class QColor;

class UTILITYSHARED_EXPORT Util
{
public:
    static QString fileName(const QString &name);
    static QString fileSuffix(const QString &name);
    static void changeQssWidgetProperty(QWidget *widget, const QString &property, const QVariant &val);
    static void refreshWidget(QWidget *widget);
    static QColor stringListToColor(const QStringList &color);
    static QStringList colorToStringList(const QColor &color);

private:
    Util();
};

#endif // UTIL_H
