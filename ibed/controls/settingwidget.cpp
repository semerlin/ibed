#include "settingwidget.h"
#include "ui_settingwidget.h"
#include "util.h"
#include "servermanger.h"
#include "netconfig.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    ui->pushButtonSave->setIcons(QStringList()
                                    << ":/res/images/upload_l.png"
                                    << ":/res/images/upload_h.png");
    ui->pushButtonSave->setText(QT_TRANSLATE_NOOP("Setting" ,"保存"));
    connect(ui->pushButtonSave, SIGNAL(pressed()), this, SLOT(onPushButtonPress()));
    connect(ui->pushButtonSave, SIGNAL(released()), this, SLOT(onPushButtonReleased()));

    //connect signals
    connect(ui->widgetServerEth, SIGNAL(reconnect(QString, quint16)),
            this, SIGNAL(reconnect(QString, quint16)));

}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::onPushButtonPress()
{
    Util::changeQssWidgetProperty(ui->pushButtonSave, "highlight", true);
    ui->pushButtonSave->changeToIcon(1);
}

void SettingWidget::onPushButtonReleased()
{
    Util::changeQssWidgetProperty(ui->pushButtonSave, "highlight", false);
    ui->pushButtonSave->changeToIcon(0);
}

void SettingWidget::setStatusText(const QString &text)
{
    ui->widgetServerEth->setStatusText(text);
}

void SettingWidget::on_pushButtonSave_clicked()
{
    saveLocal();
    saveServer();
}

void SettingWidget::saveLocal()
{
    //local save?
    QString ip = ui->widgetLocalEth->ip();
    QString netmask = ui->widgetLocalEth->netmask();
    QString gateway = ui->widgetLocalEth->gateway();
    bool needSave = false;

    if(ip != NetConfig::instance().address())
    {
        needSave = true;
        NetConfig::instance().setAddress(ip);
    }

    if(netmask != NetConfig::instance().netmask())
    {
        needSave = true;
        NetConfig::instance().setNetmask(netmask);
    }

    if(gateway != NetConfig::instance().gateway())
    {
        needSave = true;
        NetConfig::instance().setGateway(gateway);
    }


    if(needSave)
        NetConfig::instance().save();
}

void SettingWidget::saveServer()
{
    //server save?
    QString ip = ui->widgetServerEth->ip();
    quint16 port = ui->widgetServerEth->port();
    bool needSave = false;

    if(ip != ServerManger::instance().address(ServerManger::Default))
    {
        needSave = true;
        ServerManger::instance().setAddress(ServerManger::Default, ip);
    }

    if(port != ServerManger::instance().port(ServerManger::Default))
    {
        needSave = true;
        ServerManger::instance().setPort(ServerManger::Default, port);
    }

    if(needSave)
        ServerManger::instance().save();
}
