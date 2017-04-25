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
**  @file     servermanager.cpp
**  @brief    server information manage class
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "servermanager.h"
#include <QMetaType>
#include <QFile>
#include <QSettings>
#include "appsetting.h"
#include "systemcall.h"


class ServerManagerPrivate
{
public:
    void load(void);

public:
    QHash<ServerManager::ServerType, QString> m_addresses;
    QHash<ServerManager::ServerType, quint16> m_ports;

};

ServerManager::ServerManager() :
    d_ptr(new ServerManagerPrivate)
{
    qRegisterMetaType<ServerManager::ServerType>("ServerManager::ServerType");
    d_ptr->load();
}

ServerManager::~ServerManager()
{
    delete d_ptr;
}


ServerManager &ServerManager::instance(void)
{
    static ServerManager m_manger;
    return m_manger;
}

QString ServerManager::address(const ServerManager::ServerType &type) const
{
    Q_ASSERT(type < ServerManager::Count);
    return d_ptr->m_addresses[type];
}

quint16 ServerManager::port(const ServerManager::ServerType &type) const
{
    Q_ASSERT(type < ServerManager::Count);
    return d_ptr->m_ports[type];
}

void ServerManager::setAddress(const ServerManager::ServerType &type, const QString &address)
{
    Q_ASSERT(type < ServerManager::Count);
    d_ptr->m_addresses[type] = address;
}

void ServerManager::setPort(const ServerManager::ServerType &type, quint16 port)
{
    Q_ASSERT(type < ServerManager::Count);
    d_ptr->m_ports[type] = port;
}

void ServerManager::save()
{
    Q_D(ServerManager);
    QSettings setting(AppSetting::instance().
                      value(AppSetting::ServerConfig).toString(), QSettings::IniFormat);
    setting.beginGroup("Default");
    setting.setValue("address", d->m_addresses[ServerManager::Default]);
    setting.setValue("port", d->m_ports[ServerManager::Default]);
    setting.endGroup();

    setting.beginGroup("Sip");
    setting.setValue("address", d->m_addresses[ServerManager::Sip]);
    setting.setValue("port", d->m_ports[ServerManager::Sip]);
    setting.endGroup();


    SystemCall::sync();
}

void ServerManagerPrivate::load()
{
    QSettings setting(AppSetting::instance().
                      value(AppSetting::ServerConfig).toString(), QSettings::IniFormat);
    setting.beginGroup("Default");
    m_addresses[ServerManager::Default] = setting.value("address", "192.168.0.150").toString();
    m_ports[ServerManager::Default] = setting.value("port", 9000).toUInt();
    setting.endGroup();

    setting.beginGroup("Sip");
    m_addresses[ServerManager::Sip] = setting.value("address", "192.168.0.156").toString();
    m_ports[ServerManager::Sip] = setting.value("port", 5060).toUInt();
    setting.endGroup();


}
