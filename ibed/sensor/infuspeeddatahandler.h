#ifndef INFUSPEEDDATAHANDLER_H
#define INFUSPEEDDATAHANDLER_H


#include "sensor_global.h"
#include "basedatahandler.h"

class SENSORSHARED_EXPORT InfuSpeedDataHandler : public BaseDataHandler
{
    Q_OBJECT

public:
    InfuSpeedDataHandler(quint8 code, quint16 address);

public:
    void handle(quint8 code, quint16 address, const QByteArray &data);

signals:
    void speedChanged(int mount);

private:
    int m_speed;
};


#endif // INFUSPEEDDATAHANDLER_H
