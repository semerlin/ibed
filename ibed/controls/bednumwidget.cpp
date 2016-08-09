#include "bednumwidget.h"
#include "ui_bednumwidget.h"
#include <QPainter>
#include <QStyle>

BedNumWidget::BedNumWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::BedNumWidget)
{
    ui->setupUi(this);
    ui->labelBed->setText(tr("BedNum"));
    ui->labelBedNum->setText("0");
}

BedNumWidget::~BedNumWidget()
{
    delete ui;
}

void BedNumWidget::setSpacing(int spacing)
{
    ui->horizontalLayout->setSpacing(spacing);
}

void BedNumWidget::setContentsMargin(int left, int top, int right, int bottom)
{
    ui->horizontalLayout->setContentsMargins(left, top, right, bottom);
}

void BedNumWidget::setText(const QString &name)
{
    ui->labelBed->setText(name);
}

void BedNumWidget::setBedNum(int num)
{
    ui->labelBedNum->setText(QVariant(num).toString());
}

void BedNumWidget::setPixmap(const QPixmap &pixmap)
{
    ui->labelPic->setPixmap(pixmap);
}

