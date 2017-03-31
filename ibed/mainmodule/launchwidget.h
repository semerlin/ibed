#ifndef LAUNCHWIDGET_H
#define LAUNCHWIDGET_H

#include "iapplaunchwidget.h"

namespace Ui {
class LaunchWidget;
}

/**
 * @brief application launch widget
 */
class LaunchWidgetPrivate;
class LaunchWidget : public IAppLaunchWidget
{
    Q_OBJECT

public:
    explicit LaunchWidget(QWidget *parent = 0);
    ~LaunchWidget();

public:
    /**
     * @brief set launch total steps
     * @param steps - launch total steps
     */
    void setSteps(int steps);

public slots:
    void increaseStep();
    void printMsg(const QString &msg = QString());

protected:
    LaunchWidgetPrivate * const d_ptr;

private:
    Ui::LaunchWidget *ui;
    Q_DECLARE_PRIVATE(LaunchWidget);
};

#endif // LANCHWIDGET_H
