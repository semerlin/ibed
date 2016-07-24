#ifndef SERVERETHWIDGET_H
#define SERVERETHWIDGET_H

#include "basewidget.h"

namespace Ui {
class ServerEthWidget;
}

class ServerEthWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit ServerEthWidget(QWidget *parent = 0);
    ~ServerEthWidget();

private:
    Ui::ServerEthWidget *ui;
};

#endif // SERVERETHWIDGET_H
