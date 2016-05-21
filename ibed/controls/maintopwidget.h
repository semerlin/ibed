#ifndef MAINTOPWIDGET_H
#define MAINTOPWIDGET_H

#include <QWidget>

namespace Ui {
class MainTopWidget;
}

class MainTopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainTopWidget(QWidget *parent = 0);
    ~MainTopWidget();

private:
    Ui::MainTopWidget *ui;
};

#endif // MAINTOPWIDGET_H
