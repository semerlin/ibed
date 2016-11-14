#include "callbtn.h"
#include "callmange.h"
#include "sip.h"
#include "appsetting.h"
#include "servermanger.h"

CallMange::CallMange() :
    m_sip(new Sip),
    m_isIdle(true),
    m_isInited(false)
{
#ifdef TARGET_IMX
//    m_btn = new CallBtn;
//    connect(m_btn, SIGNAL(callPressed()), this, SLOT(onCallOutRequest()));
//    connect(m_btn, SIGNAL(cancelPressed()), this, SLOT(onTerminate()));
#endif

    connect(m_sip, SIGNAL(stateChanged(CallState,CallState)), this, SLOT(onStateChanged(CallState,CallState)));
}

bool CallMange::init()
{
#ifdef TARGET_IMX
//    if(!m_btn->init())
//        return false;
#endif

    initSip();

    return true;
}

void CallMange::regToServer()
{
    m_sip->reg(AppSetting::instance().value(AppSetting::DeviceNum).toString(),
                       "intellicare", ServerManger::instance().address(ServerManger::Sip));
}


void CallMange::onCallOutRequest()
{
    if(m_isIdle)
    {
        m_isIdle = false;

        m_sip->reg(AppSetting::instance().value(AppSetting::DeviceNum).toString(),
                           "intellicare", ServerManger::instance().address(ServerManger::Sip));
        m_sip->dial("0");
    }
}

void CallMange::onTerminate()
{
    m_sip->hangup();
    m_sip->reset();
    m_isIdle = true;
}


void CallMange::onStateChanged(CallState prev, CallState current)
{
    Q_UNUSED(prev)

    switch(current)
    {
    case Calling:
    case Connecting:
    case Early:
        emit callOutConnecting();
        break;
    case Incoming:
        m_isIdle = false;
        m_sip->answer();
        emit callInConnecting();
        break;
    case Confirmed:
        emit callConnected();
        break;
    case Disconnected:
        m_sip->reset();
        m_isIdle = true;
        emit callTerminate();
        break;
    default:
        break;
    }
}

void CallMange::initSip()
{
    if(m_isInited)
    {
        m_sip->destroy();
        m_isInited = false;
    }

    m_sip->setPort(ServerManger::instance().port(ServerManger::Sip));

    if(!m_sip->init())
        return;

    if(!m_sip->reg(AppSetting::instance().value(AppSetting::DeviceNum).toString(),
                   "intellicare", ServerManger::instance().address(ServerManger::Sip)))
        return;

    m_isInited = true;
}


