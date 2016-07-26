#ifndef BEDWIDGET_H
#define BEDWIDGET_H

#include <QWidget>

namespace Ui {
class BedWidget;
}

class BedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BedWidget(QWidget *parent = 0);
    ~BedWidget();

private:
    Ui::BedWidget *ui;
};

#endif // BEDWIDGET_H
