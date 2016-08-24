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

public slots:
    void setLeft(int left);
    void setSpeed(int speed);

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonReset_clicked();

signals:
    void infuStart(void);
    void infuStop(void);

private:
    Ui::InfusionWidget *ui;
};

#endif // INFUSIONWIDGET_H
