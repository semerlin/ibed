#include "powercontrol.h"
#include "pcf8574.h"

#define PCF_ADDRESS (0x20)

PowerControl &PowerControl::instance()
{
    static PowerControl m_powerCtl;
    return m_powerCtl;
}

void PowerControl::spkEnable(bool flag)
{
    char value;

    m_pcf->setAddress(PCF_ADDRESS);
    m_pcf->read(&value, 1);
    if(flag)
        value |= 0x01;
    else
        value &= 0xFE;
    m_pcf->write(&value, 1);
}

void PowerControl::rs485DirectCtrl(int direct)
{
    char value;

    m_pcf->setAddress(PCF_ADDRESS);
    m_pcf->read(&value, 1);
    if(direct != 0)
        value |= 0x10;
    else
        value &= ~(0x10);
    m_pcf->write(&value, 1);
}

void PowerControl::externalPowerOn(bool flag)
{
    char value;

    m_pcf->setAddress(PCF_ADDRESS);
    m_pcf->read(&value, 1);
    if(flag)
        value &= ~(1 << 6);
    else
        value |= 0x40;
    m_pcf->write(&value, 1);
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

