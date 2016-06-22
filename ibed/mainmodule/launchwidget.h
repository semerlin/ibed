#ifndef LAUNCHWIDGET_H
#define LAUNCHWIDGET_H

#include "iapplaunchwidget.h"

namespace Ui {
class LaunchWidget;
}

class LaunchWidget : public IAppLaunchWidget
{
    Q_OBJECT

public:
    explicit LaunchWidget(QWidget *parent = 0);
    ~LaunchWidget();
public:
    void setRange(int min, int max);

public slots:
    void increaseStep();
    void printMsg(const QString &msg);

private:
    Ui::LaunchWidget *ui;
    int m_currentVal;
    int m_maxVal;
    int m_minVal;
};

#endif // LANCHWIDGET_H
