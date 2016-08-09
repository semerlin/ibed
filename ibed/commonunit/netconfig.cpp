#include "netconfig.h"
#include <QFile>
#include "appsetting.h"
#include <QSettings>

NetConfig &NetConfig::instance()
{
    static NetConfig m_netConfig;
    return m_netConfig;
}

QString NetConfig::address() const
{
    return m_address;
}

QString NetConfig::netmask() const
{
    return m_netmask;
}

QString NetConfig::gateway() const
{
    return m_gateway;
}

void NetConfig::setAddress(const QString &ip)
{
    if(m_address != ip)
        m_address = ip;
}

void NetConfig::setNetmask(const QString &netmask)
{
    if(m_netmask != netmask)
        m_netmask = netmask;
}

void NetConfig::setGateway(const QString &gateway)
{
    if(m_gateway != gateway)
        m_gateway = gateway;
}

void NetConfig::save()
{
    QSettings setting(AppSetting::instance().
                      value(AppSetting::NetConfig).toString(), QSettings::IniFormat);

    setting.setValue("name", m_name);
    setting.setValue("ip", m_address);
    setting.setValue("netmask", m_netmask);
    setting.setValue("gateway", m_gateway);
}

void NetConfig::load()
{
    QFile file(AppSetting::instance().
               value(AppSetting::NetConfig).toString());
    if(!file.exists())
    {
        createDefault();
    }

    QSettings setting(AppSetting::instance().
                      value(AppSetting::ServerConfig).toString(), QSettings::IniFormat);


    m_name =setting.value("name", "eth0").toString();
    m_address = setting.value("ip", "192.168.0.167").toString();
    m_netmask = setting.value("netmask", "255.255.255.0").toString();
    m_gateway = setting.value("gateway", "192.168.0.1").toString();

}

NetConfig::NetConfig() :
    m_address(""),
    m_netmask(""),
    m_gateway(""),
    m_name("")
{
    load();
}

void NetConfig::createDefault()
{
    QSettings setting(AppSetting::instance().
                      value(AppSetting::NetConfig).toString(), QSettings::IniFormat);

    setting.setValue("name", "eth0");
    setting.setValue("ip", "192.168.0.167");
    setting.setValue("netmask", "255.255.255.0");
    setting.setValue("gateway", "192.168.0.1");
}
