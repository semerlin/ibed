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

static double sLastTemperValue = 0;
static double sLastHumValue = 0;

// CRC
const unsigned short POLYNOMIAL = 0x131; //P(x)=x^8+x^5+x^4+1 = 100110001

static unsigned char SHT2x_CalCrc(unsigned char data[], unsigned char nbrOfBytes)
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
    m_address(address)
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

    ::ioctl(m_fd, I2C_SLAVE, m_address);

    char data[4];
    data[0] = 0xe3;
    ::write(m_fd, data, 1);
    ::read(m_fd, data, 3);

    int val = data[0];
    val <<= 8;
    val += data[1];

    if(SHT2x_CalCrc((unsigned char*)data, 2) != data[2])
        return sLastTemperValue;

    sLastTemperValue = -46.85 + 175.72 * val / 65535;
    return sLastTemperValue;
}

double SHT20::humidity(void)
{
    if(m_fd < 0)
        return 0;

    ::ioctl(m_fd, I2C_SLAVE, m_address);

    char data[4];
    data[0] = 0xe5;
    ::write(m_fd, data, 1);
    ::read(m_fd, data, 3);

    int val = data[0];
    val <<= 8;
    val += data[1];

    if(SHT2x_CalCrc((unsigned char*)data, 2) != data[2])
        return sLastHumValue;

    sLastHumValue = -6 + 125 * val / 65535;
    return sLastHumValue;
}

