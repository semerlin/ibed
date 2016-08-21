#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <linux/i2c-dev.h>
#include "i2cdevice.h"
#include "applogger.h"


I2CDevice::I2CDevice() :
    m_fd(-1),
    m_isOpened(false)
{

}


I2CDevice::~I2CDevice()
{
    if(m_fd > 0)
        ::close(m_fd);
}


I2CDevice &I2CDevice::instance()
{
    static I2CDevice m_i2c;
    return m_i2c;
}

void I2CDevice::open()
{
    if(m_fd < 0)
    {
        m_fd = ::open("/dev/i2c-1", O_RDWR);
        if(m_fd == -1)
            AppLogger::instance().log()->error("open i2c-1 failed.");

        AppLogger::instance().log()->debug("open i2c-1 success.");

        m_isOpened = true;
    }
}

void I2CDevice::close()
{
    if(m_fd > 0)
        ::close(m_fd);

    m_isOpened = false;
}

bool I2CDevice::isOpend() const
{
    return m_isOpened;
}

void I2CDevice::setAddress(unsigned char address)
{
    if(m_fd > 0)
        ioctl(m_fd, I2C_SLAVE, address);
}

int I2CDevice::write(const QByteArray &data)
{
    return write(data.data(), data.count());
}

int I2CDevice::write(const char *data, int len)
{
    if(m_fd > 0)
    {
        int iRet = ::write(m_fd, data, len);

        if(iRet < 0)
        {
            AppLogger::instance().log()->error(QString("write to i2c-1 failed: %1.\n").arg(iRet));
            return -1;
        }

        return iRet;
    }

    return 0;
}

int I2CDevice::read(char *data, qint64 maxSize)
{
    if(m_fd > 0)
    {
        int iRet = ::read(m_fd, data, maxSize);
        if(iRet < 0)
        {
            AppLogger::instance().log()->error(QString("read from i2c-1 failed: %1.\n").arg(iRet));
            return -1;
        }

        return iRet;
    }

    return 0;
}

QByteArray I2CDevice::read(qint64 maxSize)
{
    QByteArray array;
    array.reserve(maxSize);

    if(read(array.data(), maxSize) >= 0)
        return array;

    return QByteArray();
}


