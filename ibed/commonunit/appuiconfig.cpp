#include "appuiconfig.h"
#include "appsetting.h"
#include <QFile>
#include <QSettings>
#include <QFontDatabase>
#include <QStringList>
#include <QColor>
#include "util.h"
#include <QDebug>

/* static parameters */
static const QStringList s_allParams = QStringList()
        << "Font_en"
        << "Font_zh"
        << "QssPath"
        << "LaunchQss"
        << "DefaultQss"
        << "InoutEditColor";

static const QStringList s_fontParams = QStringList()
        << "Font_en"
        << "Font_zh";

static const QStringList s_qssParams = QStringList()
        << "QssPath"
        << "LaunchQss"
        << "DefaultQss";

static const QStringList s_colorParams = QStringList()
        << "InoutEditColor";


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
        else if(s_colorParams.contains(name))
        {
            return Util::stringListToColor(m_params[name].toStringList()).rgb();
        }
    }

    return QVariant(QVariant::Invalid);
}

void AppUiConfig::setValue(AppUiConfig::Parameter param, const QVariant &val)
{
    if(s_allParams.count() > param)
    {
        QString name = s_allParams.at(param);
        m_params[name] = val;
    }
}

void AppUiConfig::save()
{
    QSettings setting(AppSetting::instance().uiConfig(), QSettings::IniFormat);
    setting.beginGroup("FONT");
    setting.setValue("en", m_params["Font_en"].toString());
    setting.setValue("zh", m_params["Font_zh"].toString());
    setting.endGroup();

    setting.beginGroup("QSS");
    setting.setValue("path", m_params["QssPath"].toString());
    setting.setValue("launch", m_params["LaunchQss"].toString());
    setting.setValue("default", m_params["DefaultQss"].toString());
    setting.endGroup();
}

QString AppUiConfig::fontFamily() const
{
   return m_fontFamily;
}

AppUiConfig::AppUiConfig() :
    m_fontFamily("")
{

}


void AppUiConfig::setDefault()
{
    QSettings setting(AppSetting::instance().uiConfig(), QSettings::IniFormat);
    setting.beginGroup("FONT");
    setting.setValue("en", "./resource/ui/font/arial.ttf");
    setting.setValue("zh", "./resource/ui/font/W3.otf");
    setting.endGroup();

    setting.beginGroup("QSS");
    setting.setValue("path", "./resource/qss");
    setting.setValue("launch", "launch.qss");
    setting.setValue("default", "default.qss");
    setting.endGroup();

    setting.beginGroup("COLOR");
    setting.setValue("inoutEditColor", Util::colorToStringList(QColor(186, 186, 186)));
    setting.endGroup();

}

void AppUiConfig::loadValue(const QString &name)
{
    //read config
    QSettings setting(name, QSettings::IniFormat);
    setting.beginGroup("FONT");
    m_params["Font_en"] = setting.value("en");
    m_params["Font_zh"] = setting.value("zh");
    setting.endGroup();
    QFontDatabase::addApplicationFont(m_params["Font_en"].toString());
    int id = QFontDatabase::addApplicationFont(m_params["Font_zh"].toString());
    QStringList list = QFontDatabase::applicationFontFamilies(id);
    m_fontFamily = list.at(0);

    setting.beginGroup("QSS");
    m_params["QssPath"] = setting.value("path");
    m_params["LaunchQss"] = setting.value("launch");
    m_params["DefaultQss"] = setting.value("default");
    setting.endGroup();

    setting.beginGroup("COLOR");
    m_params["InoutEditColor"] = setting.value("inoutEditColor");
    setting.endGroup();

}

