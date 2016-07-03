#include "patientadvisewidget.h"
#include "ui_patientadvisewidget.h"

PatientAdviseWidget::PatientAdviseWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::PatientAdviseWidget)
{
    ui->setupUi(this);
}

PatientAdviseWidget::~PatientAdviseWidget()
{
    delete ui;
}

void PatientAdviseWidget::setInfo(const QString &info)
{
    ui->labelInfo->setText(info);
}

void PatientAdviseWidget::setData(const QString &data)
{
    QString text = data;
    while(text.startsWith(' '))
        text.remove(0, 1);

    ui->textEdit->setText("      " + text);
}

void PatientAdviseWidget::setDataReadOnly(bool flag)
{
   ui->textEdit->setReadOnly(flag);
}

void PatientAdviseWidget::setPixmap(const QPixmap &pixmap)
{
    ui->labelPic->setPixmap(pixmap);
}

