#include "callinconnectedstate.h"
#include "callinconnectingstate.h"
#include "callinlocalterminatestate.h"
#include "callinremoteterminatestate.h"
#include "callin.h"
#include "calltranstraction.h"


CallIn::CallIn()
{
    m_running = new QState();

    m_connecting = new CallInConnectingState(m_running);
    m_connected = new CallInConnectedState(m_running);
    m_localTerminate = new CallInLocalTerminateState;
    m_remoteTerminate = new CallInRemoteTerminateState;

    m_running->setInitialState(m_connecting);


    CallTranstraction *tConnected = new CallTranstraction(Call::Connected);
    tConnected->setTargetState(m_connected);

    CallTranstraction *tLocalTerminate = new CallTranstraction(Call::LocalTerminate);
    tLocalTerminate->setTargetState(m_localTerminate);

    CallTranstraction *tRemoteTerminate = new CallTranstraction(Call::RemoteTerminate);
    tRemoteTerminate->setTargetState(m_remoteTerminate);

    m_connecting->addTransition(tConnected);
    m_running->addTransition(tLocalTerminate);
    m_running->addTransition(tRemoteTerminate);

    addState(m_running);
    addState(m_localTerminate);
    addState(m_remoteTerminate);

    setInitialState(m_running);
}
