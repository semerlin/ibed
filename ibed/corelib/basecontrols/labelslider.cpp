#include "labelslider.h"
#include "ui_labelslider.h"

LabelSlider::LabelSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelSlider)
{
    ui->setupUi(this);

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
}

LabelSlider::~LabelSlider()
{
    delete ui;
}

int LabelSlider::value() const
{
    return ui->horizontalSlider->value();
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

void LabelSlider::setRange(int min, int max)
{
    ui->horizontalSlider->setRange(min, max);
}

void LabelSlider::setValue(int val)
{
    ui->horizontalSlider->setValue(val);
}
