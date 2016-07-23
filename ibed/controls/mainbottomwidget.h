#ifndef MAINBOTTOMWIDGET_H
#define MAINBOTTOMWIDGET_H

#include "controls_global.h"
#include <QWidget>

namespace Ui {
class MainBottomWidget;
}

class CONTROLSSHARED_EXPORT MainBottomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainBottomWidget(QWidget *parent = 0);
    ~MainBottomWidget();

public:
    void lowlightButtons();

signals:
    void buttonClicked(int id);

private:
    void lowlightButtons(int except);

private slots:
    void onButtonClicked(int id);

private:
    Ui::MainBottomWidget *ui;
};

#endif // MAINBOTTOMWIDGET_H
