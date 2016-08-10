#include "screenwidget.h"
#include "ui_screenwidget.h"
#include "appsetting.h"

ScreenWidget::ScreenWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::ScreenWidget)
{
    ui->setupUi(this);


    ui->widgetBrightness->setRange(20, 100);
    ui->widgetBrightness->setValue(AppSetting::instance().value(AppSetting::Brightness).toInt());
    ui->widgetBrightness->setContentsMargins(0, 0, 25, 0);
    ui->widgetBrightness->setInfo(QT_TRANSLATE_NOOP("ScreenWidget", "亮度大小   "));
    ui->widgetBrightness->setPercent("  " + QString::number(AppSetting::instance().value(AppSetting::Brightness).toInt()));

    ui->widgetTime->setSpacing(10);
    ui->widgetTime->setLayoutStrech(2, 4, 1);
    ui->widgetTime->setName(QT_TRANSLATE_NOOP("ScreenWidget", "自动熄灭时间"));
    ui->widgetTime->setText(QString::number(AppSetting::instance().value(AppSetting::TurnOffTime).toInt()));

    ui->labelPic->setPixmap(QPixmap(":/res/images/screen.png"));
    ui->labelName->setText(QT_TRANSLATE_NOOP("ScreenWidget", "屏幕设置"));

    connect(ui->widgetBrightness, SIGNAL(valueChanged(int)), this, SLOT(onBrightnessChanged(int)));

}

ScreenWidget::~ScreenWidget()
{
    delete ui;
}

int ScreenWidget::brightness() const
{
    return ui->widgetBrightness->value();
}

int ScreenWidget::turnOffTime() const
{
    return ui->widgetTime->text().toInt();
}

void ScreenWidget::onBrightnessChanged(int value)
{
    ui->widgetBrightness->setPercent("  " + QString::number(value));
    emit brightnessChanged(value);
}
