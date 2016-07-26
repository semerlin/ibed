#include "labelslider.h"
#include "ui_labelslider.h"

LabelSlider::LabelSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelSlider)
{
    ui->setupUi(this);
}

LabelSlider::~LabelSlider()
{
    delete ui;
}

void LabelSlider::setInfo(const QString &info)
{
    ui->labelInfo->setText(info);
}

void LabelSlider::setPercent(const QString &percent)
{
    ui->labelPercent->setText(percent);
}

void LabelSlider::setSpacing(int spacing)
{
    ui->horizontalLayout->setSpacing(spacing);
}

void LabelSlider::setContentsMargins(int left, int top, int right, int bottom)
{
    ui->horizontalLayout->setContentsMargins(left, top, right, bottom);
}
