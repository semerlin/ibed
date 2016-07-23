#ifndef MAINTOPWIDGET_H
#define MAINTOPWIDGET_H

#include "controls_global.h"
#include <QWidget>


namespace Ui {
class MainTopWidget;
}

class QPushButton;

class CONTROLSSHARED_EXPORT MainTopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainTopWidget(QWidget *parent = 0);
    ~MainTopWidget();

public:
    void lowlightButtons();

signals:
    void buttonClicked(int id);

private:
    void lowlightButtons(int except);

private slots:
    void onButtonClicked(int id);

private:
    Ui::MainTopWidget *ui;
};

#endif // MAINTOPWIDGET_H
