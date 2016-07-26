#include "screenwidget.h"
#include "ui_screenwidget.h"

ScreenWidget::ScreenWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::ScreenWidget)
{
    ui->setupUi(this);


    ui->widgetBrightness->setContentsMargins(0, 0, 25, 0);
    ui->widgetBrightness->setInfo("Brightness   ");
    ui->widgetBrightness->setPercent("  90");
    ui->widgetTime->setLayoutStrech(2, 4, 1);
    ui->widgetTime->setName("Port");

    ui->labelPic->setPixmap(QPixmap(":/res/images/screen.png"));
    ui->labelName->setText("屏幕设置");

}

ScreenWidget::~ScreenWidget()
{
    delete ui;
}
