#include "powermange.h"


PowerMange::PowerMange() :
    m_curState(POWER_ON),
    m_idleInterval(-1),
    m_suspendInterval(5),
    m_idleCount(0),
    m_suspendCount(0),
    m_isRunning(false)
{
    m_idleTimer = new QTimer(this);
    m_idleTimer->setInterval(1000);
    connect(m_idleTimer, SIGNAL(timeout()), this, SLOT(slotPowerIdle()));

    m_suspendTimer = new QTimer(this);
    m_suspendTimer->setInterval(1000);
    connect(m_suspendTimer, SIGNAL(timeout()), this, SLOT(slotPowerSuspend()));


    m_mutex = new QMutex(QMutex::NonRecursive);
}

PowerMange::~PowerMange()
{
    disconnect(m_idleTimer, SIGNAL(timeout()), this, SLOT(slotPowerIdle()));
    disconnect(m_suspendTimer, SIGNAL(timeout()), this, SLOT(slotPowerSuspend()));

   if(m_idleTimer)
       delete m_idleTimer;

   if(m_suspendTimer)
       delete m_suspendTimer;

   if(m_mutex)
   {
       m_mutex->unlock();
       delete m_mutex;
   }
}

/**
 * @brief get PowerMange reference
 * @usage PowerMang::Instance.xxx
 * @return class reference
 */
PowerMange &PowerMange::instance()
{
    static PowerMange m_powerMange;
    return m_powerMange;
}

/**
 * @brief get current power state
 * @return
 */
POWER_STATE PowerMange::curState() const
{
    return m_curState;
}

/**
 * @brief get devices manged by this class
 * @return
 */
QSet<IDevice *> PowerMange::mangeDevices() const
{
    return m_devices;
}

/**
 * @brief get idle time interval
 * @return
 */
int PowerMange::idleInterval() const
{
    if(m_idleInterval < 0)
        return -1;

    return m_idleInterval;
}

/**
 * @brief get suspend interval after enter idle state
 * @return
 */
int PowerMange::suspendInterval() const
{
    if(m_suspendInterval < 0)
        return -1;

    return m_suspendInterval;
}

/**
 * @brief is pmu running
 * @return
 */
bool PowerMange::isRunning() const
{
   return m_isRunning;
}

/**
 * @brief run power mange unit
 */
void PowerMange::run()
{
    m_idleCount = 0;
    m_suspendCount = 0;

    m_idleTimer->start();
    m_suspendTimer->start();

    m_isRunning = true;
}

/**
 * @brief stop power mange unit
 */
void PowerMange::stop()
{
    disconnect(m_idleTimer, SIGNAL(timeout()), this, SLOT(slotPowerIdle()));
    disconnect(m_suspendTimer, SIGNAL(timeout()), this, SLOT(slotPowerSuspend()));

    if(m_idleTimer->isActive())
        m_idleTimer->stop();

    if(m_suspendTimer->isActive())
        m_suspendTimer->stop();

    m_mutex->lock();
    internalEnterState(POWER_ON);
    m_mutex->unlock();

    m_idleCount = 0;
    m_suspendCount = 0;

    m_isRunning = false;
}

/**
 * @brief set enter idle state timeout
 * @param secs: time in seconds
 */
void PowerMange::setIdleInterval(int secs)
{
    if(secs != m_idleInterval)
    {
        int prevTime = m_idleInterval;
        m_idleInterval = secs;

        m_idleCount = m_idleInterval;

        emit idleIntervalChanged(prevTime, m_idleInterval);
    }
}

/**
 * @brief time enter suspend state after enter idle state
 * @param secs: time in seconds
 */
void PowerMange::setSuspendInterval(int secs)
{
    if(m_suspendInterval != secs)
    {
        int m_prev = m_suspendInterval;
        m_suspendInterval = secs;

        m_suspendCount = m_suspendInterval;

        emit suspendIntervalChanged(m_prev, m_suspendInterval);
    }
}

/**
 * @brief enter specified power state
 * @param state
 */
void PowerMange::enterState(const POWER_STATE &state)
{
    POWER_STATE prevState = m_curState;
    m_curState = state;

    m_idleCount = 0;
    m_suspendCount = 0;

    m_mutex->lock();
    internalEnterState(m_curState);
    m_mutex->unlock();

    emit stateChanged(prevState , m_curState);
}

/**
 * @brief add devices that want to be controlled
 * @param dev
 */
void PowerMange::addDevice(IDevice *dev)
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

/**
 * @brief add devices set that want to be controlled
 * @param dev
 */
void PowerMange::addDevice(const QSet<IDevice *> &dev)
{
    m_mutex->lock();

    for(QSet<IDevice *>::const_iterator iter = dev.begin();
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

/**
 * @brief set control devices
 * @param dev
 */
void PowerMange::setDevice(const QSet<IDevice *> &dev)
{
    m_mutex->lock();
    //wakeup all old devices
    internalEnterState(POWER_ON);
    m_devices.clear();
    m_devices = dev;

    internalEnterState(m_curState);
    m_mutex->unlock();
}

/**
 * @brief remove device from this class by pointer
 * @param dev
 */
void PowerMange::removeDevice(const IDevice *dev)
{
    if(dev)
    {
        m_mutex->lock();
        for(QSet<IDevice *>::const_iterator iter = m_devices.constBegin();
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

/**
 * @brief remove device from this class by name
 * @param name
 */
void PowerMange::removeDevice(const QString &name)
{
    m_mutex->lock();
    for(QSet<IDevice *>::const_iterator iter = m_devices.constBegin();
        iter != m_devices.constEnd(); ++iter)
    {
        if((*iter)->name() == name)
        {
            (*iter)->EnterState(POWER_ON);
            m_devices.remove(*iter);
        }
    }
    m_mutex->unlock();
}

/**
 * @brief remove all devices
 */
void PowerMange::removeAllDevices(void)
{
    m_mutex->lock();

    internalEnterState(POWER_ON);
    m_devices.clear();

    m_mutex->unlock();
}

/**
 * @brief idle timeout connect slot
 */
void PowerMange::slotPowerIdle()
{
    if(m_curState == POWER_ON)
    {
        if(m_idleInterval >= 0)
        {
            if(m_idleCount ++ >= m_idleInterval)
            {
                //so enter idle state
                m_mutex->lock();
                internalEnterState(POWER_IDLE);
                m_mutex->unlock();

                m_suspendCount = 0;
                m_idleCount = 0;
            }
        }
    }
}

/**
 * @brief suspend timeout connect slot
 */
void PowerMange::slotPowerSuspend()
{
    if(m_curState == POWER_IDLE)
    {
        if(m_suspendInterval >= 0)
        {
            if(m_suspendCount ++ >= m_suspendInterval)
            {
                //so enter suspend state
                m_mutex->lock();
                internalEnterState(POWER_SUSPEND);
                m_mutex->unlock();

                m_suspendCount = 0;
                m_idleCount = 0;
            }
        }
    }
}

/**
 * @brief power on connect slot.
 * example: if tou want to enter power on state by click touchscreen,
 * you can connect mouse click event to this slot
 */
void PowerMange::slotPowerOn()
{
    if(m_curState != POWER_ON)
    {
        //enter power on state
        m_mutex->lock();
        internalEnterState(POWER_ON);
        m_mutex->unlock();
    }

    m_idleCount = 0;
    m_suspendCount = 0;
}

/**
 * @brief enter specified power state, none thread safe, just used
 *        by internal code
 * @param state: power state to enter
 */
void PowerMange::internalEnterState(const POWER_STATE &state)
{
    m_curState = state;

    for(QSet<IDevice *>::const_iterator iter = m_devices.constBegin();
        iter != m_devices.constEnd(); ++iter)
    {
        if(*iter != NULL)
        {
            (*iter)->EnterState(state);
        }
    }
}


