#include "screenwidget.h"
#include "ui_screenwidget.h"

ScreenWidget::ScreenWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::ScreenWidget)
{
    ui->setupUi(this);


    ui->widgetBrightness->setContentsMargins(0, 0, 25, 0);
    ui->widgetBrightness->setInfo(QT_TRANSLATE_NOOP("ScreenWidget", "亮度大小   "));
    ui->widgetBrightness->setPercent("  90");
    ui->widgetTime->setSpacing(10);
    ui->widgetTime->setLayoutStrech(2, 4, 1);
    ui->widgetTime->setName(QT_TRANSLATE_NOOP("ScreenWidget", "自动熄灭时间"));

    ui->labelPic->setPixmap(QPixmap(":/res/images/screen.png"));
    ui->labelName->setText(QT_TRANSLATE_NOOP("ScreenWidget", "屏幕设置"));

}

ScreenWidget::~ScreenWidget()
{
    delete ui;
}
