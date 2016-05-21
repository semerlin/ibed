#ifndef POWERMANGE_H
#define POWERMANGE_H

#include "hardware_global.h"
#include <QObject>
#include <QSet>
#include <QTimer>
#include <QMutex>
#include "powerdef.h"
#include "idevice.h"

/**
 * @brief system power mangement, devices that remove from or
 *        uncontrolled by this unit will set to POWER_ON state
 *
 *        POWER_ON->POWER_IDLE->POWER_SUSPEND
 *        POWER_IDLE/POWER_SUSPEND->POEWR_ON
 */
class HARDWARESHARED_EXPORT PowerMange : public QObject
{
   Q_OBJECT

public:
    static PowerMange &instance(void);

public:
    POWER_STATE curState(void) const;
    QSet<IDevice *> mangeDevices(void) const;
    int idleInterval(void) const;
    int suspendInterval(void) const;
    bool isRunning(void) const;
public slots:
    void run(void);
    void stop(void);
    void setIdleInterval(int secs = -1);
    void setSuspendInterval(int secs = 5);
    void enterState(const POWER_STATE &state);
    void addDevice(IDevice *dev);
    void addDevice(const QSet<IDevice *> &dev);
    void setDevice(const QSet<IDevice *> &dev);
    void removeDevice(const IDevice *dev);
    void removeDevice(const QString &name);
    void removeAllDevices(void);

signals:
    void stateChanged(const POWER_STATE &prevState, const POWER_STATE &curState);
    void idleIntervalChanged(quint32 prevTime, quint32 curTime);
    void suspendIntervalChanged(quint32 prevTime, quint32 curTime);

private slots:
    void slotPowerIdle(void);
    void slotPowerSuspend(void);
    //wakeup slots, bind event that user want to use to wakeup all devices
    void slotPowerOn(void);

private:
    void wakeupDevice(const IDevice *dev);
    void wakeupDevice(const QString &name);
    void internalEnterState(const POWER_STATE &state);

private:
    /**
     * @brief devices that controlled by this class
     */
    QSet<IDevice *> m_devices;
    POWER_STATE m_curState; //current power state

    QMutex *m_mutex;

    QTimer *m_idleTimer;
    QTimer *m_suspendTimer;
    int m_idleInterval;
    int m_suspendInterval;
    int m_idleCount;
    int m_suspendCount;

    bool m_isRunning;
private:
    PowerMange();
    ~PowerMange();
};

#endif // POWERMANGE_H
