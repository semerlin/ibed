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

void PowerControl::rs485DirectCtrl(int direct)
{
    char value;

    pcf8574_read(&value);
    if(direct != 0)
        value |= 0x10;
    else
        value &= ~(0x10);
    pcf8574_write(value);
}

void PowerControl::externalPowerOn(bool flag)
{
    char value;

    pcf8574_read(&value);
    if(flag)
        value &= ~(1 << 6);
    else
        value |= 0x40;
    pcf8574_write(value);
}

PowerControl::PowerControl()
{
    pcf8574_init();
}

PowerControl::~PowerControl()
{
    externalPowerOn(false);
    pcf8574_deinit();
}

