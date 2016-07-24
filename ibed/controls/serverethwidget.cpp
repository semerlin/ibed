#include "serverethwidget.h"
#include "ui_serverethwidget.h"

ServerEthWidget::ServerEthWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::ServerEthWidget)
{
    ui->setupUi(this);
}

ServerEthWidget::~ServerEthWidget()
{
    delete ui;
}
