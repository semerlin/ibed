#include "serverethwidget.h"
#include "ui_serverethwidget.h"

ServerEthWidget::ServerEthWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::ServerEthWidget)
{
    ui->setupUi(this);

    ui->widgetIp->setLayoutStrech(2, 4, 1);
    ui->widgetIp->setName(QT_TRANSLATE_NOOP("Server", "IP地址"));
    ui->widgetPort->setLayoutStrech(2, 4, 1);
    ui->widgetPort->setName(QT_TRANSLATE_NOOP("Server", "端口"));

    ui->labelPic->setPixmap(QPixmap(":/res/images/server.png"));
    ui->labelName->setText(QT_TRANSLATE_NOOP("Server", "服务器网络设置"));

}

ServerEthWidget::~ServerEthWidget()
{
    delete ui;
}
