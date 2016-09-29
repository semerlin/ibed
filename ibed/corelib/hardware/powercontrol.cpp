#include "powercontrol.h"
#include "pcf8574.h"

#define PCF_ADDRESS (0x20)

PowerControl &PowerControl::instance()
{
    static PowerControl m_powerCtl;
    return m_powerCtl;
}

bool PowerControl::lcdEnable(bool flag)
{
    char value;

    if(m_pcf->setAddress(PCF_ADDRESS) == -1)
        return false;

   if(m_pcf->read(&value, 1) == -1)
       return false;

    if(flag)
        value |= 0x02;
    else
        value &= ~(0x02);
    if(m_pcf->write(&value, 1) == -1)
        return false;

    return true;
}

bool PowerControl::spkEnable(bool flag)
{
    char value;

    if(m_pcf->setAddress(PCF_ADDRESS) == -1)
        return false;

    if(m_pcf->read(&value, 1) == -1)
        return false;

    if(flag)
        value |= 0x01;
    else
        value &= ~(0x01);

    if(m_pcf->write(&value, 1) == -1)
        return false;

    return true;
}

bool PowerControl::rs485DirectCtrl(int direct)
{
    char value;

    if(m_pcf->setAddress(PCF_ADDRESS) == -1)
        return false;

    if(m_pcf->read(&value, 1) == -1)
        return false;

    if(direct != 0)
        value |= 0x10;
    else
        value &= ~(0x10);

    if(m_pcf->write(&value, 1) == -1)
        return false;

    return true;
}

bool PowerControl::externalPowerOn(bool flag)
{
    char value;

    if(m_pcf->setAddress(PCF_ADDRESS) == -1)
        return false;

    if(m_pcf->read(&value, 1) == -1)
        return false;

    if(flag)
        value &= ~(0x40);
    else
        value |= 0x40;

    if(m_pcf->write(&value, 1) == -1)
        return false;

    return true;
}

PowerControl::PowerControl() :
    m_pcf(new PCF8574("/dev/i2c-0", 0x20))
{
    m_pcf->open();
}

PowerControl::~PowerControl()
{
    externalPowerOn(false);
    delete m_pcf;
}

