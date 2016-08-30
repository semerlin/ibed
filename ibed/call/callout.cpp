#include "calloutconnectedstate.h"
#include "calloutconnectingstate.h"
#include "calloutlocalterminatestate.h"
#include "calloutremoteterminatestate.h"
#include "callout.h"
#include "calltranstraction.h"


CallOut::CallOut()
{
    m_running = new QState();

    m_connecting = new CallOutConnectingState(m_running);
    m_connected = new CallOutConnectedState(m_running);
    m_localTerminate = new CallOutLocalTerminateState;
    m_remoteTerminate = new CallOutRemoteTerminateState;

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

    connect(m_connecting, SIGNAL(connecting()), this, SIGNAL(connecting()));
    connect(m_connected, SIGNAL(connected()), this, SIGNAL(connected()));
    connect(m_localTerminate, SIGNAL(terminate()), this, SIGNAL(localTerminate()));
    connect(m_remoteTerminate, SIGNAL(terminate()), this, SIGNAL(remoteTerminate()));
}

