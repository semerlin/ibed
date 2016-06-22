#include "appuiconfig.h"
#include "appsetting.h"
#include <QFile>
#include <QSettings>
#include <QFontDatabase>

AppUiConfig &AppUiConfig::instance()
{
    static AppUiConfig m_uiConfig;
    return m_uiConfig;
}

bool AppUiConfig::initialize()
{
    QString fileName = AppSetting::instance().uiConfig();
    QFile file(fileName);
    if(file.exists())
    {
        //read config
        QSettings setting(fileName, QSettings::IniFormat);
        setting.beginGroup("FONT");
        m_font = setting.value("font").toString();
        setting.endGroup();
        QFontDatabase::addApplicationFont(m_font);
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

QString AppUiConfig::font() const
{
    return m_font;
}

AppUiConfig::AppUiConfig() :
    m_font("")
{

}

void AppUiConfig::setDefault()
{
    QSettings setting(AppSetting::instance().uiConfig(), QSettings::IniFormat);
    setting.beginGroup("FONT");
    setting.setValue("font", "./resource/ui/font/A.otf");
    QFontDatabase::addApplicationFont(m_font);
    setting.endGroup();
}

