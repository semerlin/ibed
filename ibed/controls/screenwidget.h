#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include "basewidget.h"

namespace Ui {
class ScreenWidget;
}

class ScreenWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit ScreenWidget(QWidget *parent = 0);
    ~ScreenWidget();

private:
    Ui::ScreenWidget *ui;
};

#endif // SCREENWIDGET_H
