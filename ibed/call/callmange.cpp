#include "callbtn.h"
#include "callout.h"
#include "callin.h"
#include "callmange.h"
#include "callevent.h"

CallMange::CallMange() :
    m_btn(new CallBtn)
{
    connect(m_btn, SIGNAL(callPressed()), this, SLOT(onCallOutRequest()));
    connect(m_btn, SIGNAL(cancelPressed()), this, SLOT(onLocalTerminate()));

    m_callOut = new CallOut;
    m_callIn = new CallIn;

    m_activeMachine = NULL;
}

void CallMange::onCallOutRequest()
{
    if(m_activeMachine == NULL)
    {
        m_activeMachine = m_callOut;
        m_activeMachine->start();
    }
}

void CallMange::onCallInRequest()
{
    if(m_activeMachine == NULL)
    {
        m_activeMachine = m_callIn;
        m_callIn->start();
    }

}

void CallMange::onConnected()
{
    if(m_activeMachine != NULL)
        m_activeMachine->postEvent(new CallEvent(Call::Connected));
}

void CallMange::onLocalTerminate()
{
    if(m_activeMachine != NULL)
    {
        m_activeMachine->postEvent(new CallEvent(Call::LocalTerminate));
        m_activeMachine = NULL;
    }
}

void CallMange::onRemoteTerminate()
{
    if(m_activeMachine != NULL)
    {
        m_activeMachine->postEvent(new CallEvent(Call::RemoteTerminate));
        m_activeMachine = NULL;
    }
}


