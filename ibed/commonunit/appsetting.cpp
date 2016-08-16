#include "appsetting.h"
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QStringList>

#define SETTING_FILE ("./resource/setting/appsetting.ini")


/* static parameters */
static const QStringList s_allParams = QStringList()
        << "LogConfig"
        << "UiConfig"
        << "ServerConfig"
        << "NetConfig"
        << "EduAudioPath"
        << "DriverConfig"
        << "Brightness"
        << "Sound"
        << "TurnOffTime";


AppSetting &AppSetting::instance()
{
    static AppSetting m_appSetting;
    return m_appSetting;
}

bool AppSetting::initialize()
{
    QFile file(SETTING_FILE);
    if(!file.exists())
    {
        //create default file
        setDefault();
    }

    //read config
    QSettings setting(SETTING_FILE, QSettings::IniFormat);
    setting.beginGroup("Config");
    m_params["LogConfig"] = setting.value("logConfig", "./resource/setting/log.conf").toString();
    m_params["UiConfig"] = setting.value("uiConfig", "./resource/setting/appuiconfig.ini").toString();
    m_params["ServerConfig"] = setting.value("netConfig", "./resource/setting/serverconfig.ini").toString();
    m_params["NetConfig"] = setting.value("netConfig", "./resource/setting/interfaces").toString();
    m_params["DriverConfig"] = setting.value("driverConfig", "./resource/driver").toString();
    m_params["EduAudioPath"] = setting.value("eduPath", "./resource/education").toString();
    setting.endGroup();

    setting.beginGroup("Common");
    m_params["Brightness"] = setting.value("brightness", 100).toUInt();
    m_params["Sound"] = setting.value("sound", 100).toUInt();
    m_params["TurnOffTime"] = setting.value("turnofftime", 20).toUInt();
    setting.endGroup();

    return true;
}

QVariant AppSetting::value(AppSetting::Parameter param) const
{
    if(s_allParams.count() > param)
    {
        return m_params[s_allParams.at(param)];
    }

    return QVariant();
}

void AppSetting::setValue(AppSetting::Parameter param, const QVariant &val)
{
    if(s_allParams.count() > param)
    {
        m_params[s_allParams.at(param)] = val;
    }
}

void AppSetting::save()
{
    QSettings setting(SETTING_FILE, QSettings::IniFormat);

    setting.beginGroup("Common");
    setting.setValue("brightness", m_params["Brightness"]);
    setting.setValue("sound", m_params["Sound"]);
    setting.setValue("turnofftime", m_params["TurnOffTime"]);
    setting.endGroup();
}

AppSetting::AppSetting()
{

}

void AppSetting::setDefault()
{
    QSettings setting(SETTING_FILE, QSettings::IniFormat);
    setting.beginGroup("Config");
    setting.setValue("logConfig", "./resource/setting/log.conf");
    setting.setValue("uiConfig", "./resource/setting/appuiconfig.ini");
    setting.setValue("serverConfig", "./resource/setting/serverconfig.ini");
    setting.setValue("netConfig", "./resource/setting/interfaces");
    setting.setValue("driverConfig", "./resource/driver");
    setting.setValue("eduPath", "./resource/education");
    setting.endGroup();

    setting.beginGroup("Common");
    setting.setValue("brightness", 100);
    setting.setValue("sound", 100);
    setting.setValue("turnofftime", 20);
    setting.endGroup();

}
