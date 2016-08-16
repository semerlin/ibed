#ifndef POWERCONTROL_H
#define POWERCONTROL_H

#include "hardware_global.h"

class HARDWARESHARED_EXPORT PowerControl
{
public:
    static PowerControl &instance();

public:
    void spkEnable(bool flag);

private:
    PowerControl();
    ~PowerControl();
};

#endif // POWERCONTROL_H
