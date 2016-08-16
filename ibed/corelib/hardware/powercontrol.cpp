#include "powercontrol.h"
#include "pcf8574.h"

PowerControl &PowerControl::instance()
{
    static PowerControl m_powerCtl;
    return m_powerCtl;
}

void PowerControl::spkEnable(bool flag)
{
    char value;

    pcf8574_read(&value);
    if(flag)
        value |= 0x01;
    else
        value &= 0xFE;
    pcf8574_write(value);
}

PowerControl::PowerControl()
{
    pcf8574_init();
}

PowerControl::~PowerControl()
{
    pcf8574_deinit();
}

