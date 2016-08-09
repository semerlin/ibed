#ifndef LOCALETHWIDGET_H
#define LOCALETHWIDGET_H

#include "basewidget.h"

namespace Ui {
class LocalEthWidget;
}

class LocalEthWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit LocalEthWidget(QWidget *parent = 0);
    ~LocalEthWidget();

public:
    QString ip(void) const;
    QString netmask(void) const;
    QString gateway(void) const;

private:
    Ui::LocalEthWidget *ui;
};

#endif // LOCALETHWIDGET_H
