#ifndef MAINBOTTOMWIDGET_H
#define MAINBOTTOMWIDGET_H

#include <QWidget>

namespace Ui {
class MainBottomWidget;
}

class MainBottomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainBottomWidget(QWidget *parent = 0);
    ~MainBottomWidget();

private:
    Ui::MainBottomWidget *ui;
};

#endif // MAINBOTTOMWIDGET_H
