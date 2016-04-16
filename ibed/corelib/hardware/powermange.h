#ifndef POWERMANGE_H
#define POWERMANGE_H

#include "hardware_global.h"
#include <QObject>
#include <QSet>
#include <QTimer>
#include <QMutex>
#include "powerdef.h"

class IPowerMangeDevice;

/**
 * @brief system power mangement, devices that remove from or
 *        uncontrolled by this unit will set to POWER_ON state
 */
class HARDWARESHARED_EXPORT PowerMange : public QObject
{
   Q_OBJECT

public:
    static PowerMange &instance(void);

public:
    POWER_STATE curState(void) const;
    QSet<IPowerMangeDevice *> mangeDevices(void) const;

public slots:
    void setIdleInterval(int secs);
    void EnterState(const POWER_STATE &state);
    void addDevice(IPowerMangeDevice *dev);
    void addDevice(const QSet<IPowerMangeDevice *> &dev);
    void setDevice(const QSet<IPowerMangeDevice *> &dev);
    void removeDevice(const IPowerMangeDevice *dev);
    void removeDevice(const QString &name);
    void removeAllDevices(void);

signals:
    void stateChanged(const POWER_STATE &prevState, const POWER_STATE &curState);
    void idleIntervalTimeChanged(quint32 prevTime, quint32 curTime);

private slots:
    void updateState(void);

private:
    void wakeupDevice(const IPowerMangeDevice *dev);
    void wakeupDevice(const QString &name);
    void internalEnterState(const POWER_STATE &state);

private:
    /**
     * @brief devices that controlled by this class
     */
    QSet<IPowerMangeDevice *> m_devices;
    POWER_STATE m_curState; //current power state

    QTimer *m_timer;
    int m_idleInterval;

    QMutex *m_mutex;
private:
    PowerMange();
    ~PowerMange();
};

#endif // POWERMANGE_H
