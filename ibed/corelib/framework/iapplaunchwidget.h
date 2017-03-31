#ifndef IAPPLAUNCHRWIDGET_H
#define IAPPLAUNCHRWIDGET_H

#include "framework_global.h"
#include <QWidget>

/**
 * @brief launchwidget framework
 */
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
    virtual void increaseStep(void) = 0;

    /**
     * @brief show some lanch messages on the widget
     * @param msg - messages want to show
     */
    virtual void printMsg(const QString &msg) = 0;
};

#endif // IAPPLANCHERWIDGET_H

