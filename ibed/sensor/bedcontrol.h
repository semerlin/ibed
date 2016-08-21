#ifndef BEDCONTROL_H
#define BEDCONTROL_H

#include "sensor_global.h"
#include <QObject>
#include "modbus.h"
#include <QSet>

class SerialPortCtrl;
class QMutex;
class IDataHandler;

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
    unsigned short motorCurrent(void) const;
    unsigned short chargeCurrent(void) const;
    unsigned short dischargeCurrent(void) const;
    unsigned short highBatteryVoltage(void) const;
    unsigned short lowBatteryVoltage(void) const;
    quint8 weight(void) const;

    void addDataHandler(IDataHandler *handler);

public slots:
    void powerOn(void);
    void powerOff(void);
    void motorMove(int id, MotorDirection direction);

private slots:
    void onDataReached(const QByteArray &data);


private:
    BedControl();
    ~BedControl();
    Modbus *m_modbus;
    static const unsigned char m_address = 0x0a;
    QByteArray m_data;
    QMutex *m_mutex;
    mutable quint8 m_contentLen;
    QList<IDataHandler *> m_handlers;
};

#endif // BEDCONTROL_H
