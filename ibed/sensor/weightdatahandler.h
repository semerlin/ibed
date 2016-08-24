#ifndef WEIGHTDATAHANDLER_H
#define WEIGHTDATAHANDLER_H

#include "sensor_global.h"
#include "basedatahandler.h"

class SENSORSHARED_EXPORT WeightDataHandler : public BaseDataHandler
{
    Q_OBJECT

public:
    WeightDataHandler(quint8 code, quint16 address);

public:
    void handle(quint8 code, quint16 address, const QByteArray &data);

signals:
    void weightChanged(double weight);

private:
    double m_weight;

};

#endif // HEARTRATEDATAHANDLER_H
