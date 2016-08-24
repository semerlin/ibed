#include "pcf8574.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

PCF8574::PCF8574(const QString &port, quint8 address) :
    m_fd(-1),
    m_port(port),
    m_address(address)
{

}

PCF8574::~PCF8574()
{
    close();
}

bool PCF8574::open()
{
    m_fd = ::open(m_port.toLatin1().data(), O_RDWR);
    if(m_fd == -1)
    {
        printf("[PCF8574::Error] open %s failed", m_port.toLatin1().data());
        return false;
    }

    ::ioctl(m_fd, I2C_SLAVE, m_address);

    return true;
}

void PCF8574::close()
{
    ::close(m_fd);
    m_fd = -1;
}

void PCF8574::setPort(const QString &port)
{
    m_port = port;
}

void PCF8574::setAddress(quint8 address)
{
    m_address = address;
    if(m_fd >= 0)
        ::ioctl(m_fd, I2C_SLAVE, m_address);
}

quint64 PCF8574::write(const QByteArray &data)
{
    if(m_fd < 0)
        return 0;

    return ::write(m_fd, data.data(), data.count());
}

quint64 PCF8574::write(const char *data, quint64 maxSize)
{
    if(m_fd < 0)
        return 0;

    return ::write(m_fd, data, maxSize);
}

QByteArray PCF8574::read(quint64 maxSize)
{
    if(m_fd < 0)
        return QByteArray();

    QByteArray data;
    data.reserve(maxSize);
    if(::read(m_fd, data.data(), maxSize) < 0)
        printf("[PCF8574::Error] read from '%s 0x%x' failed", m_port.toLatin1().data(),
               m_address);

    return data;
}

qint64 PCF8574::read(char *data, qint64 maxSize)
{
    if(m_fd < 0)
        return 0;

    return ::read(m_fd, data, maxSize);
}
