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

signals:
    void buttonPress(int id);
    void buttonReleased(int id);

private:
    void initButtons(void);

private slots:
    void onButtonPress(void);
    void onButtonReleased(void);

private:
    Ui::BedWidget *ui;
};

#endif // BEDWIDGET_H
