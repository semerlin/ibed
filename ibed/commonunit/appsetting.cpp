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
        //read config
        QSettings setting(SETTING_FILE, QSettings::IniFormat);
        setting.beginGroup("LOG");
        m_logConfig = setting.value("logConfig").toString();
        setting.endGroup();

        setting.beginGroup("UI");
        m_uiConfig = setting.value("uiConfig").toString();
        setting.endGroup();
    }
    else
    {
        //judge whether file exists
        if(!file.open(QIODevice::ReadWrite))
            return false;

        file.close();

        //create default file
        setDefault();
    }

    return true;
}

QString AppSetting::logConfig() const
{
    return m_logConfig;
}

QString AppSetting::uiConfig() const
{
    return m_uiConfig;
}

AppSetting::AppSetting() :
    m_logConfig(""),
    m_uiConfig("")
{

}

void AppSetting::setDefault()
{
    QSettings setting(SETTING_FILE, QSettings::IniFormat);
    m_logConfig = "./resource/setting/log.conf";
    setting.beginGroup("LOG");
    setting.setValue("logConfig", m_logConfig);
    setting.endGroup();

    m_uiConfig = "./resource/setting/appuiconfig.ini";
    setting.beginGroup("UI");
    setting.setValue("uiConfig", m_uiConfig);
    setting.endGroup();
}
