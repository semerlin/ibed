#include "bedwidget.h"
#include "ui_bedwidget.h"

BedWidget::BedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BedWidget)
{
    ui->setupUi(this);
}

BedWidget::~BedWidget()
{
    delete ui;
}
