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
        m_enFont = setting.value("en").toString();
        m_cnFont = setting.value("cn").toString();
        setting.endGroup();
        QFontDatabase::addApplicationFont(m_enFont);
        QFontDatabase::addApplicationFont(m_cnFont);

        setting.beginGroup("QSS");
        m_qssPath = setting.value("path").toString();
        m_defaultQss = setting.value("default").toString();
        m_launchQss = setting.value("launch").toString();
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

QString AppUiConfig::enFont() const
{
    return m_enFont;
}

QString AppUiConfig::cnFont() const
{
    return m_cnFont;
}

QString AppUiConfig::qssPath() const
{
    return m_qssPath;
}

QString AppUiConfig::launchQss() const
{
    return m_launchQss;
}

QString AppUiConfig::defaultQss() const
{
    return m_defaultQss;
}


AppUiConfig::AppUiConfig() :
    m_cnFont(""),
    m_enFont(""),
    m_defaultQss(""),
    m_launchQss(""),
    m_qssPath("")
{
}

void AppUiConfig::setDefault()
{
    QSettings setting(AppSetting::instance().uiConfig(), QSettings::IniFormat);
    setting.beginGroup("FONT");
    setting.setValue("en", "./resource/ui/font/arial.otf");
    setting.setValue("cn", "./resource/ui/font/W3.otf");
    QFontDatabase::addApplicationFont(m_enFont);
    QFontDatabase::addApplicationFont(m_cnFont);
    setting.endGroup();

    setting.beginGroup("QSS");
    setting.setValue("path", "./resource/qss");
    setting.setValue("default", "default.qss");
    setting.setValue("launch", "launch.qss");
    setting.endGroup();
}

