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
        << "NetConfig";


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
    setting.beginGroup("LOG");
    m_params["LogConfig"] = setting.value("logConfig", "./resource/setting/log.conf").toString();
    setting.endGroup();

    setting.beginGroup("UI");
    m_params["UiConfig"] = setting.value("uiConfig", "./resource/setting/appuiconfig.ini").toString();
    setting.endGroup();

    setting.beginGroup("SERVER");
    m_params["ServerConfig"] = setting.value("netConfig", "./resource/setting/serverconfig.ini").toString();
    setting.endGroup();

    setting.beginGroup("NET");
    m_params["NetConfig"] = setting.value("netConfig", "./resource/setting/interfaces").toString();
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

AppSetting::AppSetting()
{

}

void AppSetting::setDefault()
{
    QSettings setting(SETTING_FILE, QSettings::IniFormat);
    setting.beginGroup("LOG");
    setting.setValue("logConfig", "./resource/setting/log.conf");
    setting.endGroup();

    setting.beginGroup("UI");
    setting.setValue("uiConfig", "./resource/setting/appuiconfig.ini");
    setting.endGroup();

    setting.beginGroup("SERVER");
    setting.setValue("serverConfig", "./resource/setting/serverconfig.ini");
    setting.endGroup();

    setting.beginGroup("NET");
    setting.setValue("netConfig", "./resource/setting/interfaces");
    setting.endGroup();

}
