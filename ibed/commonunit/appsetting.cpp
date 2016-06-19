#include "appsetting.h"
#include <QSettings>
#include <QFile>
#include <QDebug>

#define SETTING_FILE ("./resource/setting/appsetting.ini")

AppSetting &AppSetting::instance()
{
    static AppSetting m_appSetting;
    return m_appSetting;
}

bool AppSetting::initialize()
{
    QFile file(SETTING_FILE);
    if(file.exists())
    {
        QSettings setting(SETTING_FILE, QSettings::IniFormat);
        setting.beginGroup("LOG");
        m_logConfig = setting.value("logConfig").toString();
        setting.endGroup();
    }
    else
    {
        if(!file.open(QIODevice::ReadWrite))
            return false;

        file.close();

        setDefault();
    }

    return true;
}

QString AppSetting::logConfig() const
{
    return m_logConfig;
}

AppSetting::AppSetting()
{

}

void AppSetting::setDefault()
{
    QSettings setting(SETTING_FILE, QSettings::IniFormat);
    m_logConfig = "./resource/setting/log.conf";
    setting.beginGroup("LOG");
    setting.setValue("logConfig", m_logConfig);
    setting.endGroup();

}
