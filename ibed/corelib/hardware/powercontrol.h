#ifndef POWERCONTROL_H
#define POWERCONTROL_H

#include "hardware_global.h"

class PCF8574;

class HARDWARESHARED_EXPORT PowerControl
{
public:
    static PowerControl &instance();

public:
    bool lcdEnable(bool flag);
    bool spkEnable(bool flag);
    /**
     * @brief control max485 read and write
     * @param direct: 0 read
     *                !0 write
     */
    bool rs485DirectCtrl(int direct);

    bool externalPowerOn(bool flag);

private:
    PowerControl();
    ~PowerControl();
    PCF8574 *m_pcf;
};

#endif // POWERCONTROL_H
