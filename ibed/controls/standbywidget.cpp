#include "standbywidget.h"
#include "dotlabel.h"
#include "ui_standbywidget.h"

StandbyWidget::StandbyWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::StandbyWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->widgetInfusion->setPixmap(QString(":/res/images/infusion.png"));
    ui->widgetInfusion->setText("100%");
    ui->widgetSound->setPixmap(QString(":/res/images/sound1.png"));
    ui->widgetSound->setText("0");
    ui->widgetBrightness->setPixmap(QString(":/res/images/brightness.png"));
    ui->widgetBrightness->setText("0");
    ui->widgetTemper->setPixmap(QString(":/res/images/temper.png"));
    ui->widgetTemper->setText("100");
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
    ui->widgetNursery->setText("一级护理");
    ui->widgetNursery->setDotColor(QColor(255, 0, 0));
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
