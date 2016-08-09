#include "servermanger.h"
#include <QMetaType>
#include <QFile>
#include <QSettings>
#include "appsetting.h"


ServerManger::ServerManger()
{
    qRegisterMetaType<ServerManger::ServerType>("ServerManger::ServerType");
    load();
}


ServerManger &ServerManger::instance(void)
{
    static ServerManger m_manger;
    return m_manger;
}

QString ServerManger::address(const ServerManger::ServerType &type) const
{
    return m_addresses[type];
}

quint16 ServerManger::port(const ServerManger::ServerType &type) const
{
    return m_ports[type];
}

void ServerManger::setAddress(const ServerManger::ServerType &type, const QString &address)
{
    m_addresses[type] = address;
}

void ServerManger::setPort(const ServerManger::ServerType &type, quint16 port)
{
    m_ports[type] = port;
}

void ServerManger::save()
{
    QSettings setting(AppSetting::instance().
                      value(AppSetting::ServerConfig).toString(), QSettings::IniFormat);
    setting.beginGroup("Default");
    setting.setValue("address", m_addresses[ServerManger::Default]);
    setting.setValue("port", m_ports[ServerManger::Default]);
    setting.endGroup();

    setting.beginGroup("Monitor");
    setting.setValue("address", m_addresses[ServerManger::Monitor]);
    setting.setValue("port", m_ports[ServerManger::Monitor]);
    setting.endGroup();
}

void ServerManger::load()
{
    QFile file(AppSetting::instance().
               value(AppSetting::ServerConfig).toString());
    if(!file.exists())
    {
        createDefault();
    }

    QSettings setting(AppSetting::instance().
                      value(AppSetting::ServerConfig).toString(), QSettings::IniFormat);
    setting.beginGroup("Default");
    m_addresses[ServerManger::Default] = setting.value("address", "192.168.0.150").toString();
    m_ports[ServerManger::Default] = setting.value("port", 9000).toUInt();
    setting.endGroup();

    setting.beginGroup("Monitor");
    m_addresses[ServerManger::Monitor] = setting.value("address", "192.168.0.150").toString();
    m_ports[ServerManger::Monitor] = setting.value("port", 9000).toUInt();
    setting.endGroup();
}

void ServerManger::createDefault()
{
    QSettings setting(AppSetting::instance().
                      value(AppSetting::ServerConfig).toString(), QSettings::IniFormat);
    setting.beginGroup("Default");
    setting.setValue("address", "192.168.0.150");
    setting.setValue("port", 9000);
    setting.endGroup();

    setting.beginGroup("Monitor");
    setting.setValue("address", "192.168.0.11");
    setting.setValue("port", 3000);
    setting.endGroup();
}
