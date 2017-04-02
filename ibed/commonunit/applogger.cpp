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
**  @file     applogger.cpp
**  @brief    application logger
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#include "applogger.h"
#include "appsetting.h"
#include "log4qt/propertyconfigurator.h"
#include <QFile>

LOG4QT_DECLARE_STATIC_LOGGER(appLog, App)

AppLogger &AppLogger::instance()
{
    static AppLogger m_appLog;
    return m_appLog;
}

bool AppLogger::initialize()
{
    QString fileName = AppSetting::instance().value(AppSetting::LogConfig).toString();
    if(!QFile(fileName).exists())
        return false;

    return Log4Qt::PropertyConfigurator::configure(AppSetting::instance().
                                                   value(AppSetting::LogConfig).toString());
}

Log4Qt::Logger *AppLogger::log()
{
    return appLog();
}

AppLogger::AppLogger()
{

}

