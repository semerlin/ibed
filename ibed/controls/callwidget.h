#ifndef CALLWIDGET_H
#define CALLWIDGET_H

#include <QWidget>
#include "basewidget.h"

namespace Ui {
class CallWidget;
}

class CallWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit CallWidget(QWidget *parent = 0);
    ~CallWidget();

signals:
    void reject();

private slots:
    void on_pushButtonCancel_clicked();

private:
    Ui::CallWidget *ui;
};

#endif // CALLWIDGET_H
