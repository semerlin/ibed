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

public:
    int brightness(void) const;
    int turnOffTime(void) const;

signals:
    void brightnessChanged(int value);

private slots:
    void onBrightnessChanged(int value);

private:
    Ui::ScreenWidget *ui;
};

#endif // SCREENWIDGET_H
