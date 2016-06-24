#ifndef IAPPLAUNCHRWIDGET_H
#define IAPPLAUNCHRWIDGET_H

#include "framework_global.h"
#include <QWidget>

class FRAMEWORKSHARED_EXPORT IAppLaunchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IAppLaunchWidget(QWidget *parent = NULL) :
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
    virtual void printMsg(const QString &msg) {Q_UNUSED(msg)}
};

#endif // IAPPLANCHERWIDGET_H

