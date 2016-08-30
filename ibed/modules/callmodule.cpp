#include "callmange.h"
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
    connect(m_callMange, SIGNAL(callOutConnected()), this, SIGNAL(callOutConnected()));
    connect(m_callMange, SIGNAL(callOutLocalTerminate()), this, SIGNAL(callOutLocalTerminate()));
    connect(m_callMange, SIGNAL(callOutRemoteTerminate()), this, SIGNAL(callOutRemoteTerminate()));

    return true;
}

void CallModule::unload()
{
    delete m_callMange;
}
