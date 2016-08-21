#ifndef POWERCONTROL_H
#define POWERCONTROL_H

#include "hardware_global.h"

class HARDWARESHARED_EXPORT PowerControl
{
public:
    static PowerControl &instance();

public:
    void spkEnable(bool flag);
    /**
     * @brief control max485 read and write
     * @param direct: 0 read
     *                !0 write
     */
    void rs485DirectCtrl(int direct);

    void externalPowerOn(bool flag);

private:
    PowerControl();
    ~PowerControl();
};

#endif // POWERCONTROL_H
