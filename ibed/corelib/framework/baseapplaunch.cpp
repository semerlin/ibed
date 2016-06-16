#include "baseapplaunch.h"
#include <QApplication>
#include "log4qt/logger.h"
#include "boost/foreach.hpp"
#include <QStringList>
#include <QThread>

LOG4QT_DECLARE_STATIC_LOGGER(log,SimpleStateMachine)


BaseAppLaunch::BaseAppLaunch(IAppLaunchWidget *widget, ModuleManger *manger) :
    m_widget(widget),
    m_moduleManger(manger),
    m_thread(new QThread)
{
    Q_ASSERT(m_moduleManger != NULL);
    Q_ASSERT(m_widget != NULL);


    //load module may cost a lot of time, so move it to thread
    //don't use module that contains GUI, GUI must run in main thread
    m_moduleManger->moveToThread(m_thread);
    m_thread->start();


    connect(this, SIGNAL(startLaunch(const QVariant&)),
            m_moduleManger, SLOT(onLoadModules(const QVariant&)));

    connect(m_moduleManger, SIGNAL(moduleChanged(IAppModule*,ModuleManger::MODULE_STATUS)),
            this, SLOT(onModuleChanged(IAppModule*,ModuleManger::MODULE_STATUS)));

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

    if(m_thread->isRunning())
        m_thread->quit();
}

int BaseAppLaunch::run(int argc, char **argv)
{
    m_widget->show();

    QStringList val;
    for(int i = 0; i < argc; ++i)
    {
        val << argv[i];
    }

    QVariant moduleVal = QVariant(val);

    emit startLaunch(moduleVal);

    return 0;
}

int BaseAppLaunch::restart()
{
    return 0;
}

void BaseAppLaunch::onModuleChanged(IAppModule *module, ModuleManger::MODULE_STATUS status)
{
    if(status == ModuleManger::MODULE_LOADING)
    {
        m_widget->increaseStep();
        QString name = module->name();
        m_widget->printMsg(tr("loading module '%1' ").arg(module->name()));
    }
    else if(status == ModuleManger::MODULE_LOADED)
    {
        m_widget->increaseStep();
        m_widget->printMsg(tr("load module '%1' success").arg(module->name()));
    }
    else if(status == ModuleManger::MODULE_LOAD_FAILED)
    {
        m_widget->printMsg(tr("load module '%1 failed!").arg(module->name()));
        m_widget->printMsg(tr("error message = %1.").arg(module->error()));
    }
}





