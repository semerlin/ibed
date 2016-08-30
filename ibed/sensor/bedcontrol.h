#ifndef BEDCONTROL_H
#define BEDCONTROL_H

#include "sensor_global.h"
#include <QObject>
#include <QList>
#include <QQueue>


class Modbus;
class BedDataProcess;
class QThread;
class BedDataSend;

class SENSORSHARED_EXPORT BedControl : public QObject
{
    Q_OBJECT
public:
    typedef enum
    {
        Forword,
        Reversal,
        Stop,

        Count,

    }MotorDirection;
public:
    static BedControl &instance(void);

public slots:
    void powerOn(void);
    void powerOff(void);
    void motorMove(int id, MotorDirection direction);
    void motorMove(QList<int> id, MotorDirection direction);

    void getMotorCurrent(void) const;
    void getChargeCurrent(void) const;
    void getDischargeCurrent(void) const;
    void getHighBatteryVoltage(void) const;
    void getLowBatteryVoltage(void) const;
    void getInfusionCount(void) const;
    void getInfusionSpeed(void) const;
    void getInfusionMount(void) const;
    void getWeight(void) const;

signals:
    void infuCountChanged(int count);
    void infuSpeedChanged(int speed);
    void infuMountChanged(int mount);
    void weightChanged(double weight);

private:
    BedControl();
    ~BedControl();
    Modbus *m_modbus;
    BedDataProcess *m_process;
    QThread *m_dataProcessThread;

private:
    friend class BedDataSend;
    BedDataSend *m_send;
};

#endif // BEDCONTROL_H
