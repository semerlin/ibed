#include "powermange.h"
#include "ipowermangedevice.h"


PowerMange::PowerMange() :
    m_curState(POWER_ON),
    m_idleInterval(-1)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateState()));
//    m_timer->setInterval();

    m_mutex = new QMutex(QMutex::NonRecursive);
}


PowerMange &PowerMange::instance()
{
    static PowerMange m_powerMange;
    return m_powerMange;
}

POWER_STATE PowerMange::curState() const
{
    return m_curState;
}

QSet<IPowerMangeDevice *> PowerMange::mangeDevices() const
{
    return m_devices;
}

void PowerMange::setIdleInterval(int secs)
{
    if(secs != m_idleInterval)
    {
        int prevTime = -1;
        prevTime = m_idleInterval;

        m_idleInterval = secs;
        //stop monitor timer
        //TODO must release mutex before  stop timer
        if(m_timer->isActive())
            m_timer->stop();


        m_mutex->lock();
        //idle time changed, so wakeup all devices first
        internalEnterState(POWER_ON);
        m_mutex->unlock();

        if(m_idleInterval >= 0)
        {
            //restart timer
            m_timer->setInterval(m_idleInterval * 1000);
            m_timer->start();
        }
        else
            m_timer->setInterval(-1);

        emit idleIntervalTimeChanged();
    }
}

void PowerMange::EnterState(const POWER_STATE &state)
{
    if(m_curState != state)
    {
        m_prevState = m_curState;
        m_curState = state;

        m_mutex->lock();
        internalEnterState(m_curState);
        m_mutex->unlock();

        emit stateChanged(m_prevState , m_curState);
    }
}

void PowerMange::addDevice(IPowerMangeDevice *dev)
{
    if(dev)
    {
        m_mutex->lock();

        //enter current power state first
        dev->EnterState(m_curState);

        m_devices.insert(dev);

        m_mutex->unlock();
    }
}

void PowerMange::addDevice(const QSet<IPowerMangeDevice *> &dev)
{
    m_mutex->lock();

    for(QSet<IPowerMangeDevice *>::const_iterator iter = dev.begin();
        iter != dev.end(); ++iter)
    {
        if(*iter)
        {
            (*iter)->EnterState(m_curState);
            m_devices.insert(*iter);
        }
    }

    m_mutex->unlock();
}

void PowerMange::setDevice(const QSet<IPowerMangeDevice *> &dev)
{
    m_mutex->lock();
    //wakeup all old devices
    internalEnterState(POWER_ON);
    m_devices.clear();
    m_devices = dev;

    internalEnterState(m_curState);
    m_mutex->unlock();
}

void PowerMange::removeDevice(const IPowerMangeDevice *dev)
{
    if(dev)
    {
        m_mutex->lock();
        for(QSet<IPowerMangeDevice *>::const_iterator iter = m_devices.constBegin();
            iter != m_devices.constEnd(); ++iter)
        {
            if(*iter == dev)
            {
                (*iter)->EnterState(POWER_ON);
                m_devices.remove(*iter);
            }
        }
        m_mutex->unlock();
    }
}

void PowerMange::removeDevice(const QString &name)
{
    m_mutex->lock();
    for(QSet<IPowerMangeDevice *>::const_iterator iter = m_devices.constBegin();
        iter != m_devices.constEnd(); ++iter)
    {
        if((*iter)->deviceName() == name)
        {
            (*iter)->EnterState(POWER_ON);
            m_devices.remove(*iter);
        }
    }
    m_mutex->unlock();
}

void PowerMange::removeAllDevices(void)
{
    m_mutex->lock();

    internalEnterState(POWER_ON);
    m_devices.clear();

    m_mutex->unlock();
}



void PowerMange::updateState(void)
{

}


void PowerMange::internalEnterState(const POWER_STATE &state)
{
    for(QSet<IPowerMangeDevice *>::const_iterator iter = m_devices.constBegin();
        iter != m_devices.constEnd(); ++iter)
    {
        if(*iter != NULL)
        {
            (*iter)->EnterState(state);
        }
    }
}


