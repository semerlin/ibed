#ifndef UTIL_H
#define UTIL_H

#include "utility_global.h"

class QWidget;
class QVariant;

class UTILITYSHARED_EXPORT Util
{
public:
    static QString fileName(const QString &name);
    static QString fileSuffix(const QString &name);
    static void changeQssWidgetProperty(QWidget *widget, const QString &property, const QVariant &val);
    static void refreshWidget(QWidget *widget);

private:
    Util();
};

#endif // UTIL_H
