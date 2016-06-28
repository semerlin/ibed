#ifndef UTIL_H
#define UTIL_H

#include "utility_global.h"

class QWidget;
class QVariant;

class UTILITYSHARED_EXPORT Util
{
public:
    static Util& instance(void);
    QString fileName(const QString &name);
    QString fileSuffix(const QString &name);
    void changeQssWidgetProperty(QWidget *widget, const QString &property, const QVariant &val);
    void refreshWidget(QWidget *widget);

private:
    Util();
};

#endif // UTIL_H
