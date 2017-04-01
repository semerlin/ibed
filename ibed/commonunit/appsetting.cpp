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
**  along with OST. If not, see <http://www.gnu.org/licenses/>.
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
**
**  @file     appsetting.cpp
**  @brief    application global settings
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "appsetting.h"
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include "systemcall.h"

#define SETTING_FILE ("./resource/setting/appsetting.ini")


/* static parameters */
static const QStringList s_allParams = QStringList()
        << "DeviceNum"
        << "LogConfig"
        << "UiConfig"
        << "ServerConfig"
        << "NetConfig"
        << "EduAudioPath"
        << "DriverConfig"
        << "Brightness"
        << "Sound"
        << "TurnOffTime"
        << "ModbusPort";


AppSetting &AppSetting::instance()
{
    static AppSetting m_appSetting;
    return m_appSetting;
}

bool AppSetting::initialize()
{
    if(!QFile::exists(SETTING_FILE))
        setDefault();

    //read config
    QSettings setting(SETTING_FILE, QSettings::IniFormat);
    setting.beginGroup("Config");
    m_params["LogConfig"] = setting.value("logConfig", "./resource/setting/log.conf").toString();
    m_params["UiConfig"] = setting.value("uiConfig", "./resource/setting/appuiconfig.ini").toString();
    m_params["ServerConfig"] = setting.value("serverConfig", "./resource/setting/serverconfig.ini").toString();
    m_params["NetConfig"] = setting.value("netConfig", "./resource/setting/interfaces").toString();
    m_params["DriverConfig"] = setting.value("driverConfig", "./resource/driver").toString();
    m_params["EduAudioPath"] = setting.value("eduPath", "./resource/education").toString();
    setting.endGroup();

    setting.beginGroup("Common");
    m_params["DeviceNum"] = setting.value("device", 0).toUInt();
    m_params["Brightness"] = setting.value("brightness", 100).toUInt();
    m_params["Sound"] = setting.value("sound", 100).toUInt();
    m_params["TurnOffTime"] = setting.value("turnofftime", 20).toUInt();
    m_params["ModbusPort"] = setting.value("modbusport", "/dev/ttySP1").toString();
    setting.endGroup();

    return true;
}

QVariant AppSetting::value(AppSetting::Parameter param) const
{
    Q_ASSERT(s_allParams.count() > param);
    return m_params[s_allParams.at(param)];
}

void AppSetting::setValue(AppSetting::Parameter param, const QVariant &val)
{
    Q_ASSERT(s_allParams.count() > param);
    m_params[s_allParams.at(param)] = val;
}

void AppSetting::save()
{
    //just save "Common" settings, "Config" settings can't be modified in program
    QSettings setting(SETTING_FILE, QSettings::IniFormat);

    setting.beginGroup("Common");
    setting.setValue("device", m_params["DeviceNum"]);
    setting.setValue("brightness", m_params["Brightness"]);
    setting.setValue("sound", m_params["Sound"]);
    setting.setValue("turnofftime", m_params["TurnOffTime"]);
    setting.endGroup();

    SystemCall::sync();
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
    setting.setValue("device", 0);
    setting.setValue("brightness", 100);
    setting.setValue("sound", 100);
    setting.setValue("turnofftime", 20);
    setting.setValue("modbusport", "/dev/ttySP1");
    setting.endGroup();

}
