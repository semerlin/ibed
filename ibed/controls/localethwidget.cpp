#include "localethwidget.h"
#include "ui_localethwidget.h"

LocalEthWidget::LocalEthWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::LocalEthWidget)
{
    ui->setupUi(this);

    ui->widgetIp->setLayoutStrech(2, 3, 1);
    ui->widgetIp->setName("IP");
    ui->widgetNetmask->setLayoutStrech(2, 3, 1);
    ui->widgetNetmask->setName("NetMask");
    ui->widgetGateway->setLayoutStrech(2, 3, 1);
    ui->widgetGateway->setName("Gateway");
}

LocalEthWidget::~LocalEthWidget()
{
    delete ui;
}
