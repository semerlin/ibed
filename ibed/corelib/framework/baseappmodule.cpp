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
**  @file     baseappmodule.cpp
**  @brief    base application module class
**  @details  base application module class
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "baseappmodule.h"



BaseAppModule::BaseAppModule(const QString &name) :
    m_isLoaded(false),
    m_error("no error"),
    m_name(name),
    m_val(QVariant(QVariant::Invalid))
{
}

bool BaseAppModule::isLoaded() const
{
    return m_isLoaded;
}


bool BaseAppModule::reload()
{
    if(m_isLoaded)
        unload();

    return load(m_val);
}

void BaseAppModule::setName(const QString &name)
{
    m_name = name;
}

QString BaseAppModule::name() const
{
    return m_name;
}

QString BaseAppModule::error() const
{
    return m_error;
}
