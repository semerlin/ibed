#include "settingwidget.h"
#include "ui_settingwidget.h"
#include "util.h"
#include "servermanager.h"
#include "netconfig.h"
#include "appsetting.h"
#include "systemcall.h"
#include "netconfig.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    ui->pushButtonSave->setIcons(QStringList()
                                    << ":/res/images/save_h.png"
                                    << ":/res/images/save_l.png");
    ui->pushButtonSave->setText(QT_TRANSLATE_NOOP("Setting" ,"保存"));
    connect(ui->pushButtonSave, SIGNAL(pressed()), this, SLOT(onPushButtonPress()));
    connect(ui->pushButtonSave, SIGNAL(released()), this, SLOT(onPushButtonReleased()));

    //connect signals
    connect(ui->widgetServerEth, SIGNAL(reconnect(QString,quint16,quint16)),
            this, SLOT(onReconnect(QString,quint16,quint16)));

    connect(ui->widgetScreenWidget, SIGNAL(brightnessChanged(int)), this, SIGNAL(brightnessChanged(int)));
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

quint8 SettingWidget::deviceNum() const
{
    return ui->widgetServerEth->deviceNum();
}

void SettingWidget::on_pushButtonSave_clicked()
{
    saveLocal();
    saveServer();
    saveScreen();
}

void SettingWidget::onReconnect(const QString &ip, quint16 port, quint16 device)
{
    emit reconnect(ip, port, device,
                   ui->widgetLocalEth->ip(),
                   ui->widgetLocalEth->netmask(),
                   ui->widgetLocalEth->gateway());
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

void SettingWidget::saveScreen()
{
    bool needSave = false;
    if(ui->widgetScreenWidget->brightness() != AppSetting::instance().value(AppSetting::Brightness).toInt())
    {
        needSave = true;
        AppSetting::instance().setValue(AppSetting::Brightness, ui->widgetScreenWidget->brightness());
    }

    if(ui->widgetSound->sound() != AppSetting::instance().value(AppSetting::Sound).toInt())
    {
        needSave = true;
        AppSetting::instance().setValue(AppSetting::Sound, ui->widgetSound->sound());
    }

    if(ui->widgetScreenWidget->turnOffTime() != AppSetting::instance().value(AppSetting::TurnOffTime).toInt())
    {
        needSave = true;
        AppSetting::instance().setValue(AppSetting::TurnOffTime, ui->widgetScreenWidget->turnOffTime());
        emit turnOffTimeChanged(ui->widgetScreenWidget->turnOffTime());
    }

    if(ui->widgetServerEth->deviceNum() != AppSetting::instance().value(AppSetting::DeviceNum).toInt())
    {
        needSave = true;
        AppSetting::instance().setValue(AppSetting::DeviceNum, ui->widgetServerEth->deviceNum());
    }


    if(needSave)
        AppSetting::instance().save();
}

