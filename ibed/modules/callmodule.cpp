#include "callmanage.h"
#include "callmodule.h"


CallModule::CallModule(const QString &name) :
    BaseAppModule(name)
{

}

CallModule::~CallModule()
{

}

bool CallModule::load(const QVariant &val)
{
    Q_UNUSED(val)
    m_callMange = new CallMange;

    connect(m_callMange, SIGNAL(callOutConnecting()), this, SIGNAL(callOutConnecting()));
    connect(m_callMange, SIGNAL(callInConnecting()), this, SIGNAL(callInConnecting()));
    connect(m_callMange, SIGNAL(callConnected()), this, SIGNAL(callConnected()));
    connect(m_callMange, SIGNAL(callTerminate()), this, SIGNAL(callTerminate()));

    m_callMange->init();

    return true;
}

void CallModule::unload()
{
    delete m_callMange;
}

void CallModule::callOutRequest()
{
    m_callMange->onCallOutRequest();
}

void CallModule::callHangup()
{
    m_callMange->onTerminate();
}



