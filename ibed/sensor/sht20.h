#ifndef SHT20_H
#define SHT20_H

#include "sensor_global.h"

class SHT20
{
public:
    SHT20();

public:
    static double temperature(void);
    static double humidity(void);
};

#endif // SHT20_H
