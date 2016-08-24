#ifndef INFUMOUNTDATAHANDLER_H
#define INFUMOUNTDATAHANDLER_H


#include "sensor_global.h"
#include "basedatahandler.h"

class SENSORSHARED_EXPORT InfuMountDataHandler : public BaseDataHandler
{
    Q_OBJECT

public:
    InfuMountDataHandler(quint8 code, quint16 address);

public:
    void handle(quint8 code, quint16 address, const QByteArray &data);

signals:
    void mountChanged(int mount);

private:
    int m_mount;
};


#endif // INFUMOUNTDATAHANDLER_H
