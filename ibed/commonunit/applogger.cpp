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

