#include <QApplication>
#include "launchwidget.h"
#include "modulemanger.h"
#include "baseapplaunch.h"
#include "hardwaremodule.h"
#include "thememodule.h"
#include "appsetting.h"
#include "applogger.h"
#include "appuiconfig.h"
#include "qssloader.h"
#include "mainmodule.h"
#include <QDir>
#include <QTextCodec>
#include "appentry.h"


AppEntry &AppEntry::instance()
{
    static AppEntry m_appEntry;
    return m_appEntry;
}

int AppEntry::run(int argc, char **argv)
{
    QApplication app(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf8");
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);

    if(m_widget == NULL)
        m_widget = new LaunchWidget;

    if(m_manger == NULL)
        m_manger = new ModuleManger;

    //load base configure
    AppSetting::instance().initialize();
    AppLogger::instance().initialize();
    AppUiConfig::instance().initialize();

    AppLogger::instance().log()->info(tr("application startup"));
    //init modules
    m_manger->addModule(new ThemeModule("Theme"));
    m_manger->addModule(new HardwareModule("Hardware"));


    //launch widget qss need load first
    AppLogger::instance().log()->info("initialize launch widget ui");
    QssLoader qssLoader;
    qssLoader.loadQss(AppUiConfig::instance().value(AppUiConfig::QssPath).toString() +
                      QDir::separator() +
                      AppUiConfig::instance().value(AppUiConfig::LaunchQss).toString());


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
    if(m_mainModule == NULL)
        m_mainModule = new MainModule;
    m_mainModule->initialize();
}

AppEntry::AppEntry() :
    m_widget(NULL),
    m_manger(NULL),
    m_mainModule(NULL)
{

}

AppEntry::~AppEntry()
{
    if(m_widget)
        delete m_widget;

    if(m_manger)
        delete m_manger;

    if(m_mainModule)
        delete m_mainModule;
}
