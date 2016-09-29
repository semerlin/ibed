#include "sht20.h"
#include "i2cdevice.h"
#include "applogger.h"
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

// CRC
const unsigned short POLYNOMIAL = 0x131; //P(x)=x^8+x^5+x^4+1 = 100110001

static unsigned char SHT2x_CalCrc(unsigned char *data, unsigned char nbrOfBytes)
{
    unsigned char crc = 0;
    unsigned char byteCtr;
    //calculates 8-Bit checksum with given polynomial
    for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
    {
        crc ^= (data[byteCtr]);

        for(unsigned char bit = 8; bit > 0; --bit)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ POLYNOMIAL;
            else
                crc = (crc << 1);
        }
    }

    return crc;
}

SHT20::SHT20(const QString &port, const quint8 address) :
    m_fd(-1),
    m_address(address),
    m_temper(0),
    m_humidity(0)
{
    m_fd = ::open(port.toLatin1().data(), O_RDWR);
    if(m_fd == -1)
        AppLogger::instance().log()->error(QString("open %1 failed.").arg(port));

//    AppLogger::instance().log()->debug(QString("open %1 success.").arg(port));
}

SHT20::~SHT20()
{
    ::close(m_fd);
    m_fd = -1;
}

double SHT20::temperature(void)
{
    if(m_fd < 0)
        return 0;

    if(::ioctl(m_fd, I2C_SLAVE, m_address) == -1)
    {
        AppLogger::instance().log()->error("set sht20 address failed!");
        return m_temper;
    }

    char data[4];
    data[0] = 0xe3;
    if(::write(m_fd, data, 1) == -1)
    {
        AppLogger::instance().log()->error("write to sht20 address failed!");
        return m_temper;
    }

    if(::read(m_fd, data, 3) == -1)
    {
        AppLogger::instance().log()->error("read from sht20 address failed!");
        return m_temper;
    }

    int val = data[0];
    val <<= 8;
    val += data[1];

    if(SHT2x_CalCrc((unsigned char*)data, 2) != data[2])
        return m_temper;

    m_temper = -46.85 + 175.72 * val / 65535;
    return m_temper;
}

double SHT20::humidity(void)
{
    if(m_fd < 0)
        return 0;

    if(::ioctl(m_fd, I2C_SLAVE, m_address) == -1)
    {
        AppLogger::instance().log()->error("set sht20 address failed!");
        return m_temper;
    }

    char data[4];
    data[0] = 0xe5;
    if(::write(m_fd, data, 1) == -1)
    {
        AppLogger::instance().log()->error("write to sht20 address failed!");
        return m_temper;
    }

    if(::read(m_fd, data, 3) == -1)
    {
        AppLogger::instance().log()->error("read from sht20 address failed!");
        return m_temper;
    }

    int val = data[0];
    val <<= 8;
    val += data[1];

    if(SHT2x_CalCrc((unsigned char*)data, 2) != data[2])
        return m_humidity;

    m_humidity = -6 + 125 * val / 65535;
    return m_humidity;
}

