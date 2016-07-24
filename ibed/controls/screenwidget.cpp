#include "screenwidget.h"
#include "ui_screenwidget.h"

ScreenWidget::ScreenWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::ScreenWidget)
{
    ui->setupUi(this);
}

ScreenWidget::~ScreenWidget()
{
    delete ui;
}
