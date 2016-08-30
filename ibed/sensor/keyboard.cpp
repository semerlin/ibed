#include "pcf8574.h"
#include "keyboard.h"
#include <QDebug>

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
    m_pcf->setAddress(m_address);
    if(m_pcf->read((char *)&val, 1) < 0)
    {
        qDebug() << "read keyboard failed, address: " << m_address;
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
    m_pcf->setAddress(m_address);
    if(m_pcf->read((char *)&val, 1) < 0)
    {
        qDebug() << "read keyboard failed, address: " << m_address;
        return keys;
    }

    for(int i = 0; i < 8; ++i)
    {
        if((val & (1 << i)) != 0)
            keys.append(i);
    }

    return keys;
}
