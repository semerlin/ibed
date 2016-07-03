#include "patientinfowidget.h"
#include "ui_patientinfowidget.h"

PatientInfoWidget::PatientInfoWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::PatientInfoWidget)
{
    ui->setupUi(this);
}

PatientInfoWidget::~PatientInfoWidget()
{
    delete ui;
}

void PatientInfoWidget::setContentsMargins(int left, int top, int right, int bottom)
{
    ui->verticalLayout->setContentsMargins(left, top, right, bottom);
}

void PatientInfoWidget::setData(const QString &data)
{
    ui->labelData->setText(data);
}

void PatientInfoWidget::setInfo(const QString &info)
{
    ui->labelInfo->setText(info);
}

void PatientInfoWidget::setPixmap(const QPixmap &pixmap)
{
    ui->labelPic->setPixmap(pixmap);
}
