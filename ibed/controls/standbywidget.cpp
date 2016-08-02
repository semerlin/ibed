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
    ui->widgetSound->setText("100");
    ui->widgetBrightness->setPixmap(QString(":/res/images/brightness.png"));
    ui->widgetBrightness->setText("100");
    ui->widgetTemper->setPixmap(QString(":/res/images/temper.png"));
    ui->widgetTemper->setText("100");
    ui->widgetWeight->setPixmap(QString(":/res/images/bedweight.png"));
    ui->widgetWeight->setText("100Kg");

    ui->labelName->setText("司马大叔");

    ui->widgetBed->setText("病床号12");
    ui->widgetNursery->setText("特级护理");
    ui->widgetAge->setText("100岁");
}

StandbyWidget::~StandbyWidget()
{
    delete ui;
}

void StandbyWidget::setName(const QString &name)
{

}

void StandbyWidget::setBedNum(int num)
{

}

void StandbyWidget::setNursery(int level)
{

}

void StandbyWidget::setAge(int age)
{

}
