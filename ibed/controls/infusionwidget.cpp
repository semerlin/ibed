#include "infusionwidget.h"
#include "ui_infusionwidget.h"
#include "circleprogressbar.h"

InfusionWidget::InfusionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfusionWidget)
{
    ui->setupUi(this);

    ui->progressBarLeft->setText("55");
    ui->progressBarLeft->setValue(55);

    ui->progressBarSpeed->setCircleStyle(CircleProgressBar::Dash);
    ui->progressBarSpeed->setText("90");
    ui->progressBarSpeed->setValue(90);

    ui->labelLeft->setText(tr("输液剩余%1").arg("55%"));
    ui->labelSpeed->setText(tr("滴速%1滴/秒").arg(90));

    ui->pushButtonStart->setText(tr("开 始"));
    ui->pushButtonStop->setText(tr("停 止"));
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonReset->setText(tr("清 零"));
    ui->pushButtonReset->setEnabled(false);

}

InfusionWidget::~InfusionWidget()
{
    delete ui;
}
