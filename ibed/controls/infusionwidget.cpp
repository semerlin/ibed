#include "infusionwidget.h"
#include "ui_infusionwidget.h"

InfusionWidget::InfusionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfusionWidget)
{
    ui->setupUi(this);
}

InfusionWidget::~InfusionWidget()
{
    delete ui;
}
