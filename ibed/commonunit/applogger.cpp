#include "applogger.h"
#include "appsetting.h"
#include "log4qt/propertyconfigurator.h"

LOG4QT_DECLARE_STATIC_LOGGER(appLog, App)

AppLogger &AppLogger::instance()
{
    static AppLogger m_appLog;
    return m_appLog;
}

void AppLogger::initialize()
{
    Log4Qt::PropertyConfigurator::configure(AppSetting::instance().logConfig());
}

Log4Qt::Logger *AppLogger::log()
{
    return appLog();
}

AppLogger::AppLogger()
{

}

