#ifndef IDATAHANDLER_H
#define IDATAHANDLER_H

#include "sensor.h"
#include <QObject>

class SENSORSHARED_EXPORT IDataHandler : public QObject
{
public:
    IDataHandler() {}
    virtual ~IDataHandler() {}

public:
    virtual quint8 fucCode(void) const = 0;
    virtual quint16 regAddress(void) const = 0;
    virtual void handle(quint8 code, quint16 address, const QByteArray &data) = 0;
};

#endif // IHANDLEDATA_H
