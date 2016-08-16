#ifndef LIGHTINTENSITY_H
#define LIGHTINTENSITY_H

#include "sensor_global.h"

class SENSORSHARED_EXPORT LightIntensity
{
public:
    static LightIntensity& instance();

public:
    int intensity(void) const;

private:
    LightIntensity();
    ~LightIntensity();
    int m_fd;
};

#endif // LIGHTINTENSITY_H
