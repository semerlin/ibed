/*****************************************************************************
**
**  Copyright (C) 2016-2017 HuangYang
**
**  This file is part of IBED
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License version 3 as
**  published by the Free Software Foundation.
**
**  You should have received a copy of the GNU General Public License
**  along with this program. If not, see <http://www.gnu.org/licenses/>.
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
**
**  @file     appuiconfig.cpp
**  @brief    application ui environment
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "appuiconfig.h"
#include "appsetting.h"
#include <QFile>
#include <QSettings>
#include <QFontDatabase>
#include <QStringList>
#include <QColor>
#include "util.h"
#include "systemcall.h"

/* static parameters */
static const QStringList s_allParams = QStringList()
        << "SkinPath"
        << "LaunchQss"
        << "ApplicationQss"
        << "InoutEditColor"
        << "MusicSelectBackground";

static const QStringList s_qssParams = QStringList()
        << "SkinPath"
        << "LaunchQss"
        << "ApplicationQss";

static const QStringList s_colorParams = QStringList()
        << "InoutEditColor"
        << "MusicSelectBackground";

static const QStringList s_fontParams = QStringList()
        << "Font_En"
        << "Font_Zh";


class AppUiConfigPrivate
{
public:
    void setDefault(void);
    void loadValue(const QString &name);

    inline QString getFontFamily(int id)
    {
        QStringList list = QFontDatabase::applicationFontFamilies(id);
        return list.at(0);
    }

public:
    QHash<QString, QVariant> m_params;
    QHash<QString, QString> m_fontFamily;
};


AppUiConfig &AppUiConfig::instance()
{
    static AppUiConfig m_uiConfig;
    return m_uiConfig;
}

bool AppUiConfig::initialize()
{
    Q_D(AppUiConfig);
    QString fileName = AppSetting::instance().
            value(AppSetting::UiConfig).toString();
    if(!QFile::exists(fileName))
        d->setDefault();

    d->loadValue(fileName);

    return true;
}

QVariant AppUiConfig::value(AppUiConfig::Parameter param) const
{
    Q_ASSERT(s_allParams.count() > param);
    QString name = s_allParams.at(param);

    if(s_qssParams.contains(name))
        return d_ptr->m_params[name];
    else
    {
        Q_ASSERT(s_colorParams.contains(name));
        return Util::stringListToColor(d_ptr->m_params[name].toStringList()).rgb();
    }
}

void AppUiConfig::setValue(AppUiConfig::Parameter param, const QVariant &val)
{
    Q_ASSERT(s_allParams.count() > param);
    Q_D(AppUiConfig);
    d->m_params[s_allParams.at(param)] = val;
}

void AppUiConfig::save()
{
    Q_D(AppUiConfig);
    QSettings setting(AppSetting::instance().
                      value(AppSetting::UiConfig).toString(), QSettings::IniFormat);

    //save "Skin" and "Color" configure, "Font" configure can't be nodified in program
    setting.beginGroup("Skin");
    setting.setValue("path", d->m_params["SkinPath"].toString());
    setting.setValue("launch", d->m_params["LaunchQss"].toString());
    setting.setValue("application", d->m_params["ApplicationQss"].toString());
    setting.endGroup();

    setting.beginGroup("Color");
    setting.setValue("inoutEditColor", Util::colorToStringList(QColor(186, 186, 186)));
    setting.setValue("musicSelectBackground", Util::colorToStringList(QColor(100, 181, 237)));
    setting.endGroup();

    SystemCall::sync();
}

QString AppUiConfig::fontFamily(AppFont font) const
{
    Q_ASSERT(s_fontParams.count() > font);
    return d_ptr->m_fontFamily[s_fontParams.at(font)];
}

AppUiConfig::AppUiConfig() :
    d_ptr(new AppUiConfigPrivate)
{

}

AppUiConfig::~AppUiConfig()
{
    delete d_ptr;
}


void AppUiConfigPrivate::setDefault()
{
    QSettings setting(AppSetting::instance().
                      value(AppSetting::UiConfig).toString(), QSettings::IniFormat);
    setting.beginGroup("Font");
    setting.setValue("en", "./resource/ui/font/arial.ttf");
    setting.setValue("zh", "./resource/ui/font/W3.otf");
    setting.endGroup();

    setting.beginGroup("Skin");
    setting.setValue("path", "./resource/skin");
    setting.setValue("launch", "launch.qss");
    setting.setValue("application", "default.qss");
    setting.endGroup();

    setting.beginGroup("Color");
    setting.setValue("inoutEditColor", Util::colorToStringList(QColor(186, 186, 186)));
    setting.setValue("musicSelectBackground", Util::colorToStringList(QColor(100, 181, 237)));
    setting.endGroup();
}

void AppUiConfigPrivate::loadValue(const QString &name)
{
    //read config
    QSettings setting(name, QSettings::IniFormat);
    setting.beginGroup("Font");
    QString fontEn = setting.value("en", "./resource/ui/font/arial.ttf").toString();
    QString fontZh = setting.value("zh", "./resource/ui/font/W3.otf").toString();
    setting.endGroup();
    m_fontFamily["Font_En"] = getFontFamily(QFontDatabase::addApplicationFont(fontEn));
    m_fontFamily["Font_Zh"] = getFontFamily(QFontDatabase::addApplicationFont(fontZh));

    setting.beginGroup("Skin");
    m_params["SkinPath"] = setting.value("path", "./resource/skin");
    m_params["LaunchQss"] = setting.value("launch", "launch.qss");
    m_params["ApplicationQss"] = setting.value("application", "default.qss");
    setting.endGroup();

    setting.beginGroup("Color");
    m_params["InoutEditColor"] = setting.value("inoutEditColor", Util::colorToStringList(QColor(186, 186, 186)));
    m_params["MusicSelectBackground"] = setting.value("musicSelectBackground", Util::colorToStringList(QColor(100, 181, 237)));
    setting.endGroup();
}
