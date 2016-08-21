#ifndef BASEDATAHANDLER_H
#define BASEDATAHANDLER_H

#include "sensor_global.h"
#include "idatahandler.h"

class SENSORSHARED_EXPORT BaseDataHandler : public IDataHandler
{
public:
    explicit BaseDataHandler(quint8 code, quint16 address);
    virtual ~BaseDataHandler() {}

public:
    quint8 fucCode() const;
    quint16 regAddress() const;
    virtual void handle(quint8 code, quint16 address, const QByteArray &data);

private:
    quint16 m_fucCode;
    quint16 m_regAddress;
};


#endif // BASEDATAHANDLER_H
