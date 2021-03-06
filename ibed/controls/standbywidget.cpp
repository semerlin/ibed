#include "standbywidget.h"
#include "dotlabel.h"
#include "ui_standbywidget.h"

StandbyWidget::StandbyWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::StandbyWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->widgetHumidity->setPixmap(QString(":/res/images/humidity.png"));
    ui->widgetHumidity->setText("0%");
    ui->widgetSound->setPixmap(QString(":/res/images/sound1.png"));
    ui->widgetSound->setText("0");
    ui->widgetBrightness->setPixmap(QString(":/res/images/brightness.png"));
    ui->widgetBrightness->setText("0");
    ui->widgetTemper->setPixmap(QString(":/res/images/temper.png"));
    ui->widgetTemper->setText("0℃");
    ui->widgetWeight->setPixmap(QString(":/res/images/bedweight.png"));
    ui->widgetWeight->setText("0Kg");

    ui->labelName->setText("未知");

    ui->widgetBed->setText("病床号0");
    ui->widgetNursery->setText("三级护理");
    ui->widgetAge->setText("0岁");
}

StandbyWidget::~StandbyWidget()
{
    delete ui;
}

void StandbyWidget::setName(const QString &name)
{
    ui->labelName->setText(name);
}

void StandbyWidget::setBedNum(int num)
{
    ui->widgetBed->setText(QString("病床号%1").arg(num));
}

void StandbyWidget::setNursery(int level)
{
    switch(level)
    {
    case 0:
        ui->widgetNursery->setText("特级护理");
        ui->widgetNursery->setDotColor(QColor(255, 0, 0));
        break;
    case 1:
        ui->widgetNursery->setText("一级护理");
        ui->widgetNursery->setDotColor(QColor(255, 0, 255));
        break;
    case 2:
        ui->widgetNursery->setText("二级护理");
        ui->widgetNursery->setDotColor(QColor(0, 0, 255));
        break;
    case 3:
        ui->widgetNursery->setText("三级护理");
        ui->widgetNursery->setDotColor(QColor(255, 255, 255));
        break;
    default:
        ui->widgetNursery->setText("三级护理");
        ui->widgetNursery->setDotColor(QColor(255, 255, 255));
        break;
    }
}

void StandbyWidget::setAge(int age)
{
    ui->widgetAge->setText(QString("%1岁").arg(age));
}

void StandbyWidget::setLightIntensity(const QString &intensity)
{
    ui->widgetBrightness->setText(intensity);
}


void StandbyWidget::setAudioIntensity(const QString &intensity)
{
    ui->widgetSound->setText(intensity);
}

void StandbyWidget::setTemperature(const QString &temper)
{
    ui->widgetTemper->setText(temper);
}

void StandbyWidget::setWeight(const QString &weight)
{
    ui->widgetWeight->setText(weight);
}

void StandbyWidget::setHumidity(const QString &humidity)
{
    ui->widgetHumidity->setText(humidity);
}



