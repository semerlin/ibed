#include "pcf8574.h"
#include "keyboard.h"
#include "applogger.h"
#include "log4qt/logger.h"

Keyboard::Keyboard(const QString &port, quint8 address) :
    m_pcf(new PCF8574(port, address)),
    m_address(address)
{
    m_pcf->open();
}

Keyboard::~Keyboard()
{
    delete m_pcf;
}

quint8 Keyboard::value() const
{
    quint8 val;
    m_pcf->setAddress(m_address);
    m_pcf->read((char *)&val, 1);

    return val;
}

QList<quint8> Keyboard::pressedKeys() const
{
    QList<quint8> keys;
    quint8 val;
    if(m_pcf->setAddress(m_address) == -1)
    {
        AppLogger::instance().log()->error(QString("set keyboard(%1) address failed!").arg(m_address));
        return keys;
    }

    if(m_pcf->read((char *)&val, 1) == -1)
    {
        AppLogger::instance().log()->error(QString("read keyboard(%1) failed!").arg(m_address));
        return keys;
    }

    for(int i = 0; i < 8; ++i)
    {
        if((val & (1 << i)) == 0)
            keys.append(i);
    }

    return keys;
}

QList<quint8> Keyboard::releasedKeys() const
{
    QList<quint8> keys;
    quint8 val;
    if(m_pcf->setAddress(m_address) == -1)
    {
        AppLogger::instance().log()->error(QString("set keyboard(%1) address failed!").arg(m_address));
        return keys;
    }

    if(m_pcf->read((char *)&val, 1) == -1)
    {
        AppLogger::instance().log()->error(QString("read keyboard(%1) failed!").arg(m_address));
        return keys;
    }

    for(int i = 0; i < 8; ++i)
    {
        if((val & (1 << i)) != 0)
            keys.append(i);
    }

    return keys;
}
