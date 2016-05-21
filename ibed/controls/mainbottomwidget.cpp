#include "mainbottomwidget.h"
#include "ui_mainbottomwidget.h"

MainBottomWidget::MainBottomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainBottomWidget)
{
    ui->setupUi(this);
}

MainBottomWidget::~MainBottomWidget()
{
    delete ui;
}
