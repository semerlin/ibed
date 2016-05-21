#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "powermange.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::mousePressEvent(QMouseEvent *)
{
    PowerMange::instance().enterState(POWER_ON);
//    Backlight::instance().setValue(100);
}
