#ifndef SHT20_H
#define SHT20_H

#include "sensor_global.h"

class SHT20
{
public:
    explicit SHT20(const QString &port, const quint8 address);
    ~SHT20();

public:
    double temperature(void);
    double humidity(void);

private:
    int m_fd;
    quint8 m_address;
};

#endif // SHT20_H
