#ifndef INFUCOUNTDATAHANDLER_H
#define INFUCOUNTDATAHANDLER_H

#include "sensor_global.h"
#include "basedatahandler.h"

class SENSORSHARED_EXPORT InfuCountDataHandler : public BaseDataHandler
{
    Q_OBJECT

public:
    InfuCountDataHandler(quint8 code, quint16 address);

public:
    void handle(quint8 code, quint16 address, const QByteArray &data);

signals:
    void countChanged(int count);

private:
    int m_count;
};

#endif // INFUCOUNTDATAHANDLER_H
