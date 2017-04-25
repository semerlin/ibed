#include "baseapplaunch.h"
#include <QApplication>
#include "log4qt/logger.h"
#include "boost/foreach.hpp"
#include <QStringList>
#include <QThread>
#include <QTimer>

LOG4QT_DECLARE_STATIC_LOGGER(log, BaseAppLaunch)


BaseAppLaunch::BaseAppLaunch(IAppLaunchWidget *widget, ModuleManager *manger) :
    m_widget(widget),
    m_moduleManger(manger),
    m_extVal(QVariant())
{
    Q_ASSERT(m_moduleManger != NULL);
    Q_ASSERT(m_widget != NULL);


    connect(this, SIGNAL(startLaunch(const QVariant&)),
            m_moduleManger, SLOT(onLoadModules(const QVariant&)), Qt::QueuedConnection);

    connect(m_moduleManger, SIGNAL(moduleChanged(IAppModule*,ModuleManager::MODULE_STATUS)),
            this, SLOT(onModuleChanged(IAppModule*,ModuleManager::MODULE_STATUS)));

    BOOST_FOREACH(IAppModule *module, m_moduleManger->modules())
    {
        connect(module, SIGNAL(message(const QString&)),
                m_widget, SLOT(printMsg(const QString&)));
    }
}

BaseAppLaunch::~BaseAppLaunch()
{
    if(m_moduleManger)
    {
        disconnect(m_moduleManger, SIGNAL(moduleChanged(IAppModule*,ModuleManger::MODULE_STATUS)),
                   this, SLOT(onModuleChanged(IAppModule*,ModuleManger::MODULE_STATUS)));
    }
}

int BaseAppLaunch::run(int argc, char **argv)
{
    m_widget->show();

    QStringList val;
    for(int i = 0; i < argc; ++i)
    {
        val << argv[i];
    }

    m_extVal = val;
    //wait a little minute to let m_widget shown
    QTimer::singleShot(100, this, SLOT(onStartLaunch()));
    return 0;
}

void BaseAppLaunch::onModuleChanged(IAppModule *module, ModuleManager::MODULE_STATUS status)
{
    if(status == ModuleManager::MODULE_LOADING)
    {
        m_widget->printMsg(tr("loading module '%1' ").arg(module->name()));
    }
    else if(status == ModuleManager::MODULE_LOADED)
    {
        m_widget->increaseStep();
        m_widget->printMsg(tr("load module '%1' success").arg(module->name()));
    }
    else if(status == ModuleManager::MODULE_LOAD_FAILED)
    {
        m_widget->printMsg(tr("load module '%1 failed!").arg(module->name()));
        m_widget->printMsg(tr("error message = %1.").arg(module->error()));
    }
    else if(status == ModuleManager::MODULE_LOAD_FINISHED)
    {
        emit launchFinished();
    }
}

void BaseAppLaunch::onStartLaunch()
{
    emit startLaunch(m_extVal);
}





