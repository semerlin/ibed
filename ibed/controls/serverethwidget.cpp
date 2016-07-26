#include "serverethwidget.h"
#include "ui_serverethwidget.h"

ServerEthWidget::ServerEthWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::ServerEthWidget)
{
    ui->setupUi(this);

    ui->widgetIp->setLayoutStrech(2, 4, 1);
    ui->widgetIp->setName("IP");
    ui->widgetPort->setLayoutStrech(2, 4, 1);
    ui->widgetPort->setName("Port");

    ui->labelPic->setPixmap(QPixmap(":/res/images/server.png"));
    ui->labelName->setText("服务器网络设置");

}

ServerEthWidget::~ServerEthWidget()
{
    delete ui;
}
