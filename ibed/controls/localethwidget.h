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

private:
    Ui::LocalEthWidget *ui;
};

#endif // LOCALETHWIDGET_H
