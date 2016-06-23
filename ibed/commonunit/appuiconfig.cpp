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
        m_enFont = setting.value("enFont").toString();
        m_cnFont = setting.value("cnFont").toString();
        setting.endGroup();
        QFontDatabase::addApplicationFont(m_enFont);
        QFontDatabase::addApplicationFont(m_cnFont);
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

QString AppUiConfig::enFont() const
{
    return m_enFont;
}

QString AppUiConfig::cnFont() const
{
    return m_cnFont;
}


AppUiConfig::AppUiConfig() :
    m_cnFont(""),
    m_enFont("")
{
}

void AppUiConfig::setDefault()
{
    QSettings setting(AppSetting::instance().uiConfig(), QSettings::IniFormat);
    setting.beginGroup("FONT");
    setting.setValue("enFont", "./resource/ui/font/arial.otf");
    setting.setValue("cnFont", "./resource/ui/font/W3.otf");
    QFontDatabase::addApplicationFont(m_enFont);
    QFontDatabase::addApplicationFont(m_cnFont);
    setting.endGroup();
}

