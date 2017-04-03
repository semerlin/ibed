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
**  @file     thememodule.cpp
**  @brief    thememodule class, useed to change application themes
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include <QStringList>
#include "thememodule.h"
#include "qssloader.h"
#include <QDir>
#include <QPair>
#include "appuiconfig.h"
#include "util.h"
#include <QResource>
#include "thememodule_p.h"

ThemeModule::ThemeModule(const QString &name) :
    BaseAppModule(name),
    d_ptr(new ThemeModulePrivate)
{
}

ThemeModule::~ThemeModule()
{
    unload();
    delete d_ptr;
}

bool ThemeModule::load(const QVariant &val)
{
    Q_UNUSED(val)
    Q_D(ThemeModule);

    d->m_themes.clear();

    bool ret = false;

    //make pair qss file and its short name, for example
    //"C:/test/default.qss" and "default"
    QStringList qss = QssLoader::findAllQss(AppUiConfig::instance().
                                           value(AppUiConfig::SkinPath).toString());
    foreach(const QString &name, qss)
    {
        QString fileName;
        int splash = name.lastIndexOf(QDir::separator());
        if(splash == -1)
            fileName = name;
        else
        {
            fileName = name.mid(splash + 1);
        }

        d->m_themes[Util::fileName(fileName)] = name;
    }

    QString shortCut = Util::fileName(
                AppUiConfig::instance().
                value(AppUiConfig::LaunchQss).toString());

    //remove launch skin, we only need to change application skin in program
    if(d->m_themes.contains(shortCut))
        d->m_themes.remove(shortCut);

    //load default qss
    shortCut = Util::fileName(
                AppUiConfig::instance().
                value(AppUiConfig::ApplicationQss).toString());
    QString name;
    if(d->m_themes.contains(shortCut))
    {
        name = shortCut;
        ret = QssLoader::loadQss(d->m_themes[shortCut]);
    }
    else
    {
        name = d->m_themes.begin().key();
        ret = QssLoader::loadQss(d->m_themes.begin().value());
    }

    if(ret)
    {
        m_isLoaded = true;
        emit themeChanged(name);
    }
    else
        m_error = QString("file '%1' does not exists").arg(shortCut);

//    sleep(2);
    return ret;
}

void ThemeModule::unload()
{
    Q_D(ThemeModule);
    d->m_themes.clear();

    m_isLoaded = false;
    m_error = "no error";
}

QStringList ThemeModule::themes()
{
    Q_D(ThemeModule);
    QStringList skins;
    for(QHash<QString, QString>::const_iterator iter = d->m_themes.constBegin();
        iter != d->m_themes.constEnd(); ++iter)
    {
        skins << *iter;
    }

    return skins;
}

void ThemeModule::changeToTheme(const QString &theme)
{
    Q_D(ThemeModule);
    if(d->m_themes.contains(theme))
    {
        if(QssLoader::loadQss(d->m_themes[theme]))
            emit themeChanged(theme);
    }
}
