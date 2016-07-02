#ifndef BASEINFOWIDGET_H
#define BASEINFOWIDGET_H

#include <QWidget>

namespace Ui {
class BaseInfoWidget;
}

class BaseInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseInfoWidget(QWidget *parent = 0);
    ~BaseInfoWidget();

private:
    Ui::BaseInfoWidget *ui;
};

#endif // BASEINFOWIDGET_H
