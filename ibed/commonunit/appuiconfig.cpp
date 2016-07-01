#include "appuiconfig.h"
#include "appsetting.h"
#include <QFile>
#include <QSettings>
#include <QFontDatabase>
#include <QStringList>

/* static parameters */
static const QStringList s_allParams = QStringList()
        << "Font_en"
        << "Font_zh"
        << "QssPath"
        << "LaunchQss"
        << "DefaultQss";

static const QStringList s_fontParams = QStringList()
        << "Font_en"
        << "Font_zh";

static const QStringList s_qssParams = QStringList()
        << "QssPath"
        << "LaunchQss"
        << "DefaultQss";


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
        loadValue(fileName);
    }
    else
    {
        if(!file.open(QIODevice::ReadWrite))
            return false;

        file.close();
        setDefault();
        loadValue(fileName);
    }

    return true;
}

QVariant AppUiConfig::value(AppUiConfig::Parameter param) const
{
    if(s_allParams.count() > param)
    {
        QString name = s_allParams.at(param);

        if((s_fontParams.contains(name)) ||
           (s_qssParams.contains(name)))
        {
            return m_params[name];
        }
    }

    return QVariant(QVariant::Invalid);
}

void AppUiConfig::setValue(AppUiConfig::Parameter param, const QVariant &val)
{
    if(s_allParams.count() > param)
    {
        QString name = s_allParams.at(param);

        if((s_fontParams.contains(name)) ||
           (s_qssParams.contains(name)))
        {
            m_params[name] = val;
        }
    }
}

void AppUiConfig::save()
{

}

AppUiConfig::AppUiConfig()
{

}


void AppUiConfig::setDefault()
{
    QSettings setting(AppSetting::instance().uiConfig(), QSettings::IniFormat);
    setting.beginGroup("FONT");
    setting.setValue("en", "./resource/ui/font/arial.otf");
    setting.setValue("zh", "./resource/ui/font/W3.otf");
    setting.endGroup();

    setting.beginGroup("QSS");
    setting.setValue("path", "./resource/qss");
    setting.setValue("launch", "launch.qss");
    setting.setValue("default", "default.qss");
    setting.endGroup();
}

void AppUiConfig::loadValue(const QString &name)
{
    //read config
    QSettings setting(name, QSettings::IniFormat);
    setting.beginGroup("FONT");
    m_params["Font_en"] = setting.value("en").toString();
    m_params["Font_zh"] = setting.value("zh").toString();
    setting.endGroup();
    QFontDatabase::addApplicationFont(m_params["Font_en"].toString());
    QFontDatabase::addApplicationFont(m_params["Font_zh"].toString());

    setting.beginGroup("QSS");
    m_params["QssPath"] = setting.value("path").toString();
    m_params["LaunchQss"] = setting.value("launch").toString();
    m_params["DefaultQss"] = setting.value("default").toString();
    setting.endGroup();
}

