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
**  @file     netconfig.cpp
**  @brief    device network information
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "netconfig.h"
#include <QFile>
#include "appsetting.h"
#include <QSettings>
#include "systemcall.h"

NetConfig &NetConfig::instance()
{
    static NetConfig m_netConfig;
    return m_netConfig;
}

QString NetConfig::address() const
{
    return m_address;
}

QString NetConfig::netmask() const
{
    return m_netmask;
}

QString NetConfig::gateway() const
{
    return m_gateway;
}

QString NetConfig::name() const
{
    return m_name;
}

void NetConfig::setAddress(const QString &ip)
{
    if(m_address != ip)
        m_address = ip;
}

void NetConfig::setNetmask(const QString &netmask)
{
    if(m_netmask != netmask)
        m_netmask = netmask;
}

void NetConfig::setGateway(const QString &gateway)
{
    if(m_gateway != gateway)
        m_gateway = gateway;
}

void NetConfig::setName(const QString &name)
{
    if(m_name != name)
        m_name = name;
}

void NetConfig::save()
{
    QSettings setting(AppSetting::instance().
                      value(AppSetting::NetConfig).toString(), QSettings::IniFormat);

    setting.setValue("name", m_name);
    setting.setValue("ip", m_address);
    setting.setValue("netmask", m_netmask);
    setting.setValue("gateway", m_gateway);

    SystemCall::sync();
}

void NetConfig::load()
{
    QSettings setting(AppSetting::instance().
                      value(AppSetting::NetConfig).toString(), QSettings::IniFormat);

    m_name =setting.value("name", "eth0").toString();
    m_address = setting.value("ip", "192.168.0.167").toString();
    m_netmask = setting.value("netmask", "255.255.255.0").toString();
    m_gateway = setting.value("gateway", "192.168.0.1").toString();

}

NetConfig::NetConfig() :
    m_address(""),
    m_netmask(""),
    m_gateway(""),
    m_name("")
{
    load();
}
