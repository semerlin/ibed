#include <QApplication>
#include "launchwidget.h"
#include "modulemanger.h"
#include "baseapplaunch.h"
#include "appsetting.h"
#include "applogger.h"
#include "appuiconfig.h"
#include "qssloader.h"
#include "mainmodule.h"
#include <QDir>
#include <QTextCodec>
#include "appentry.h"
#include <QResource>
#include "mainwidget.h"


AppEntry &AppEntry::instance()
{
    static AppEntry m_appEntry;
    return m_appEntry;
}

int AppEntry::run(int argc, char **argv)
{
    QApplication app(argc, argv);



    QResource::registerResource("./resource/ui/launch.rcc");

    //support chinese
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    m_widget = new LaunchWidget;

    //load base configure
    AppSetting::instance().initialize();
    AppLogger::instance().initialize();
    AppUiConfig::instance().initialize();

    AppLogger::instance().log()->info(tr("application startup"));

    //init main module
    m_mainModule = new MainModule;

    //launch widget qss need load first
    AppLogger::instance().log()->info("initialize launch widget ui");
    QssLoader qssLoader;
    qssLoader.loadQss(m_widget, AppUiConfig::instance().value(AppUiConfig::QssPath).toString() +
                      QDir::separator() +
                      AppUiConfig::instance().value(AppUiConfig::LaunchQss).toString());


    //start lanch
    m_widget->setRange(0, m_mainModule->manger()->unloadedModules().count());

    BaseAppLaunch launcher(m_widget, m_mainModule->manger());
    connect(&launcher, SIGNAL(launchFinished()), this, SLOT(onLaunchFinished()));

    AppLogger::instance().log()->info("start launch app modules");
    launcher.run(argc, argv);

    return app.exec();
}

void AppEntry::onLaunchFinished()
{
    AppLogger::instance().log()->info(QT_TRANSLATE_NOOP("Launch", "Launch Finished!"));
    //load really finished
    m_widget->hide();
    delete m_widget;
    m_widget = NULL;

    //init main module
    m_mainModule->initialize();
}

AppEntry::AppEntry() :
    m_widget(NULL),
    m_mainModule(NULL)
{

}

AppEntry::~AppEntry()
{
    delete m_widget;
    delete m_mainModule;
}
