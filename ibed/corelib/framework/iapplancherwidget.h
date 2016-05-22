#ifndef IAPPLANCHERWIDGET_H
#define IAPPLANCHERWIDGET_H

#include "framework_global.h"
#include <QWidget>

class FRAMEWORKSHARED_EXPORT IAppLancherWidget : public QWidget
{
public:
    IAppLancherWidget();

public slots:
    /**
     * @brief increase one step
     */
    virtual void increaseStep(void) = 0;

    /**
     * @brief print some lanch messages
     * @param msg
     */
    virtual void printMsg(const QString &msg) = 0;
};

#endif // IAPPLANCHERWIDGET

