#include "baseinfowidget.h"
#include "ui_baseinfowidget.h"

BaseInfoWidget::BaseInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseInfoWidget)
{
    ui->setupUi(this);
}

BaseInfoWidget::~BaseInfoWidget()
{
    delete ui;
}
