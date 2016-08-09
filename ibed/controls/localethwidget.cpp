#include "localethwidget.h"
#include "ui_localethwidget.h"
#include "netconfig.h"

LocalEthWidget::LocalEthWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::LocalEthWidget)
{
    ui->setupUi(this);

    ui->widgetIp->setLayoutStrech(2, 4, 1);
    ui->widgetIp->setName(QT_TRANSLATE_NOOP("Local", "IP地址"));
    ui->widgetNetmask->setLayoutStrech(2, 4, 1);
    ui->widgetNetmask->setName(QT_TRANSLATE_NOOP("Local", "子网掩码"));
    ui->widgetGateway->setLayoutStrech(2, 4, 1);
    ui->widgetGateway->setName(QT_TRANSLATE_NOOP("Local", "网关"));

    ui->labelPic->setPixmap(QPixmap(":/res/images/local.png"));
    ui->labelName->setText(QT_TRANSLATE_NOOP("Local", "本机网络设置"));


    ui->widgetIp->setText(NetConfig::instance().address());
    ui->widgetNetmask->setText(NetConfig::instance().netmask());
    ui->widgetGateway->setText(NetConfig::instance().gateway());
}

LocalEthWidget::~LocalEthWidget()
{
    delete ui;
}

QString LocalEthWidget::ip() const
{
    return ui->widgetIp->text();
}

QString LocalEthWidget::netmask() const
{
    return ui->widgetNetmask->text();
}

QString LocalEthWidget::gateway() const
{
    return ui->widgetGateway->text();
}
