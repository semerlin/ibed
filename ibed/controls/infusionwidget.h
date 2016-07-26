#ifndef INFUSIONWIDGET_H
#define INFUSIONWIDGET_H

#include <QWidget>

namespace Ui {
class InfusionWidget;
}

class InfusionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InfusionWidget(QWidget *parent = 0);
    ~InfusionWidget();

private:
    Ui::InfusionWidget *ui;
};

#endif // INFUSIONWIDGET_H
