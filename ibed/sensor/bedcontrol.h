#ifndef BEDCONTROL_H
#define BEDCONTROL_H

#include "sensor_global.h"
#include <QObject>

class SerialPortCtrl;

class SENSORSHARED_EXPORT BedControl : public QObject
{
    Q_OBJECT

public:
    static BedControl &instance(void);

public slots:
    void powerOn(void);
    void powerOff(void);

private slots:
    void onDataReached(void);

private:
    BedControl();
    ~BedControl();
    SerialPortCtrl *m_serial;
};

#endif // BEDCONTROL_H
