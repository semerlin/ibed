#ifndef BASEINFOWIDGET_H
#define BASEINFOWIDGET_H

#include "controls_global.h"
#include <QWidget>

namespace Ui {
class BaseInfoWidget;
}

class CONTROLSSHARED_EXPORT BaseInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseInfoWidget(QWidget *parent = 0);
    ~BaseInfoWidget();

private:
    Ui::BaseInfoWidget *ui;
};

#endif // BASEINFOWIDGET_H
