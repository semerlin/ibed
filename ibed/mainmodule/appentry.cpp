#include <QApplication>
#include "appentry.h"
#include "baseapplaunch.h"
#include "hardwaremodule.h"
#include "qssmodule.h"
#include "appsetting.h"
#include "applogger.h"
#include "appuiconfig.h"
#include "qssloader.h"
#include <QDir>


AppEntry &AppEntry::instance()
{
    static AppEntry m_appEntry;
    return m_appEntry;
}

int AppEntry::run(int argc, char **argv)
{
    QApplication app(argc, argv);

    m_widget = new LaunchWidget;
    m_manger = new ModuleManger;

    AppSetting::instance().initialize();
    AppLogger::instance().initialize();
    AppUiConfig::instance().initialize();

    //init modules
    m_manger->addModule(&QssModule::instance());
    m_manger->addModule(&HardwareModule::instance());


    //launch widget qss need load first
    QssLoader qssLoader;
    qssLoader.loadQss(AppUiConfig::instance().qssPath() +
                      QDir::separator() +
                      AppUiConfig::instance().launchQss());

//    QssModule::instance().load(QVariant::Invalid);

    //start lanch
    m_widget->setRange(0, m_manger->unloadedModules().count());

    BaseAppLaunch launcher(m_widget, m_manger);
    connect(&launcher, SIGNAL(launchFinished()), this, SLOT(onLaunchFinished()));

    launcher.run(argc, argv);

    return app.exec();
}

void AppEntry::onLaunchFinished()
{
    //load modules that can't run in thread
    m_manger->setOutMainThread(false);
    m_manger->loadModules();
//    m_widget->hide();
}

AppEntry::AppEntry()
{

}
