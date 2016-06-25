#include <QApplication>
#include "launchwidget.h"
#include "modulemanger.h"
#include "baseapplaunch.h"
#include "hardwaremodule.h"
#include "qssmodule.h"
#include "appsetting.h"
#include "applogger.h"
#include "appuiconfig.h"
#include "qssloader.h"
#include "mainmodule.h"
#include <QDir>

#include "appentry.h"

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

    //load base configure
    AppSetting::instance().initialize();
    AppLogger::instance().initialize();
    AppUiConfig::instance().initialize();

    AppLogger::instance().log()->info(tr("application startup"));
    //init modules
    m_manger->addModule(&QssModule::instance());
    m_manger->addModule(&HardwareModule::instance());


    //launch widget qss need load first
    AppLogger::instance().log()->info("initialize launch widget ui");
    QssLoader qssLoader;
    qssLoader.loadQss(AppUiConfig::instance().qssPath() +
                      QDir::separator() +
                      AppUiConfig::instance().launchQss());


    //start lanch
    m_widget->setRange(0, m_manger->unloadedModules().count());

    BaseAppLaunch launcher(m_widget, m_manger);
    connect(&launcher, SIGNAL(launchFinished()), this, SLOT(onLaunchFinished()));

    AppLogger::instance().log()->info("start launch app modules");
    launcher.run(argc, argv);

    return app.exec();
}

void AppEntry::onLaunchFinished()
{
    //load modules that can't run in thread
    m_manger->setOutMainThread(false);
    m_manger->loadModules();

    //load really finished
    m_widget->hide();
    delete m_widget;
    m_widget = NULL;

    //init main module and startup application
    m_mainModule->initialize();
}

AppEntry::AppEntry()
{

}
