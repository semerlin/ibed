#include "serverethwidget.h"
#include "ui_serverethwidget.h"
#include "servermanager.h"
#include "appsetting.h"

ServerEthWidget::ServerEthWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::ServerEthWidget)
{
    ui->setupUi(this);

    ui->widgetIp->setLayoutStrech(2, 4, 1);
    ui->widgetIp->setName(QT_TRANSLATE_NOOP("Server", "IP地址"));
    ui->widgetPort->setLayoutStrech(2, 4, 1);
    ui->widgetPort->setName(QT_TRANSLATE_NOOP("Server", "端口"));
    ui->widgetDevice->setLayoutStrech(2, 4, 1);
    ui->widgetDevice->setName(QT_TRANSLATE_NOOP("Server", "设备号"));

    ui->labelPic->setPixmap(QPixmap(":/res/images/server.png"));
    ui->labelName->setText(QT_TRANSLATE_NOOP("Server", "服务器网络设置"));

    ui->labelStatus->setText(QT_TRANSLATE_NOOP("Server", "未链接"));

    ui->pushButtonConnect->setText(QT_TRANSLATE_NOOP("Server", "连 接"));

    ui->widgetIp->setText(ServerManager::instance().
                          address(ServerManager::Default));

    ui->widgetPort->setText(QString::number(ServerManager::instance().
                                            port(ServerManager::Default)));

    ui->widgetDevice->setText(QString::number(AppSetting::instance().value(AppSetting::DeviceNum).toInt()));
}

ServerEthWidget::~ServerEthWidget()
{
    delete ui;
}

QString ServerEthWidget::ip() const
{
    return ui->widgetIp->text();
}

quint16 ServerEthWidget::port() const
{
    return ui->widgetPort->text().toUInt();
}

quint8 ServerEthWidget::deviceNum() const
{
    return static_cast<quint8>(ui->widgetDevice->text().toUInt());
}

void ServerEthWidget::setStatusText(const QString &text)
{
    ui->labelStatus->setText(text);
}

void ServerEthWidget::on_pushButtonConnect_clicked()
{
    ui->labelStatus->setText(QT_TRANSLATE_NOOP("Server", "正在连接..."));
    emit reconnect(ui->widgetIp->text(), ui->widgetPort->text().toUInt(),
                   ui->widgetDevice->text().toUInt());
}
