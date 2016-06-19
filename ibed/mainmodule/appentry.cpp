#include <QApplication>
#include "appentry.h"
#include "baseapplaunch.h"
#include "lanchwidget.h"
#include "modulemanger.h"
#include "hardwaremodule.h"
#include "qssmodule.h"
#include "appsetting.h"
#include "applogger.h"



AppEntry &AppEntry::instance()
{
    static AppEntry m_appEntry;
    return m_appEntry;
}

int AppEntry::run(int argc, char **argv)
{
    QApplication app(argc, argv);

    AppSetting::instance().initialize();
    AppLogger::instance().initialize();

    //lancher widget
    LanchWidget widget;
    ModuleManger manger;

    //qss need load first
    QssModule::instance().load(QVariant::Invalid);
    //init modules
    manger.addModule(&HardwareModule::instance());
    manger.addModule(&QssModule::instance());

    //start lanch
    BaseAppLaunch lancher(&widget, &manger);
    lancher.run(argc, argv);

    return app.exec();
}

AppEntry::AppEntry()
{

}
