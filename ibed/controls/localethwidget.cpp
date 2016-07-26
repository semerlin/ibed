#include "localethwidget.h"
#include "ui_localethwidget.h"

LocalEthWidget::LocalEthWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::LocalEthWidget)
{
    ui->setupUi(this);

    ui->widgetIp->setLayoutStrech(2, 4, 1);
    ui->widgetIp->setName("IP");
    ui->widgetNetmask->setLayoutStrech(2, 4, 1);
    ui->widgetNetmask->setName("NetMask");
    ui->widgetGateway->setLayoutStrech(2, 4, 1);
    ui->widgetGateway->setName("Gateway");

    ui->labelPic->setPixmap(QPixmap(":/res/images/local.png"));
    ui->labelName->setText("本机网络设置");
}

LocalEthWidget::~LocalEthWidget()
{
    delete ui;
}
