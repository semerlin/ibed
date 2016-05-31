#ifndef IAPPLANCHERWIDGET_H
#define IAPPLANCHERWIDGET_H

#include "framework_global.h"
#include <QWidget>

class FRAMEWORKSHARED_EXPORT IAppLancherWidget : public QWidget
{
public:
    explicit IAppLancherWidget(QWidget *parent = NULL) :
        QWidget(parent)
    {
    }

public slots:
    /**
     * @brief increase one step
     */
    virtual void increaseStep(void) {}

    /**
     * @brief print some lanch messages
     * @param msg
     */
    virtual void printMsg(const QString &msg) {}
};

#endif // IAPPLANCHERWIDGET_H

