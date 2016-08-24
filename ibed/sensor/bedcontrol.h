#ifndef BEDCONTROL_H
#define BEDCONTROL_H

#include "sensor_global.h"
#include <QObject>
#include "modbus.h"
#include <QSet>

class SerialPortCtrl;
class QMutex;
class IDataHandler;
class KeyboardMange;

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

public:
    void addDataHandler(IDataHandler *handler);

public slots:
    void powerOn(void);
    void powerOff(void);
    void motorMove(int id, MotorDirection direction);

    void getMotorCurrent(void) const;
    void getChargeCurrent(void) const;
    void getDischargeCurrent(void) const;
    void getHighBatteryVoltage(void) const;
    void getLowBatteryVoltage(void) const;
    void getInfusionCount(void) const;
    void getInfusionSpeed(void) const;
    void getInfusionMount(void) const;
    void getWeight(void) const;

private slots:
    void onDataReached(const QByteArray &data);
    void onKeyPressed(int id);
    void onKeyReleased(int id);

private:
    BedControl();
    ~BedControl();
    Modbus *m_modbus;
    static const unsigned char m_address = 0x0a;
    QByteArray m_data;
    QMutex *m_mutex;
    mutable quint8 m_contentLen;
    QList<IDataHandler *> m_handlers;
    KeyboardMange *m_kbdMange;
};

#endif // BEDCONTROL_H
