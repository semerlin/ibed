#include "baseapplancher.h"
#include <QApplication>
#include "log4qt/logger.h"
#include "boost/foreach.hpp"
#include <QStringList>
#include <QThread>

LOG4QT_DECLARE_STATIC_LOGGER(log,SimpleStateMachine)


BaseAppLancher::BaseAppLancher(IAppLancherWidget *widget, ModuleManger *manger) :
    m_widget(widget),
    m_moduleManger(manger),
    m_thread(new QThread)
{
    Q_ASSERT(m_moduleManger != NULL);


    //load module may cost a lot of time, so move it to thread
    m_moduleManger->moveToThread(m_thread);
    m_thread->start();


    connect(this, SIGNAL(startLanch(const QVariant&)),
            m_moduleManger, SLOT(onLoadModules(const QVariant&)));

    connect(m_moduleManger, SIGNAL(moduleChanged(IAppModule*,ModuleManger::MODULE_STATUS)),
            this, SLOT(onModuleChanged(IAppModule*,ModuleManger::MODULE_STATUS)));

    BOOST_FOREACH(IAppModule *module, m_moduleManger->modules())
    {
        connect(module, SIGNAL(message(const QString&)),
                m_widget, SLOT(printMsg(const QString&)));
    }
}

BaseAppLancher::~BaseAppLancher()
{
    disconnect(m_moduleManger, SIGNAL(moduleChanged(IAppModule*,ModuleManger::MODULE_STATUS)),
               this, SLOT(onModuleChanged(IAppModule*,ModuleManger::MODULE_STATUS)));

    if(m_moduleManger)
    {
        delete m_moduleManger;
        m_moduleManger = NULL;
    }

    if(m_thread->isRunning())
        m_thread->quit();
}

int BaseAppLancher::run(int argc, char **argv)
{
    m_widget->show();

    QStringList val;
    for(int i = 0; i < argc; ++i)
    {
        val << argv[i];
    }

    QVariant moduleVal = QVariant(val);

    emit startLanch(moduleVal);

    return 0;
}

int BaseAppLancher::restart()
{
    return 0;
}

void BaseAppLancher::onModuleChanged(IAppModule *module, ModuleManger::MODULE_STATUS status)
{
    if(status == ModuleManger::MODULE_LOAD)
    {
        m_widget->increaseStep();
        m_widget->printMsg(tr("load module %1 ...").arg(module->name()));
    }
    else if(status == ModuleManger::MODULE_LOAD_FAILED)
    {
        m_widget->printMsg(tr("load module %1 failed!").arg(module->name()));
        m_widget->printMsg(tr("error message = %1.").arg(module->error()));
    }
}





