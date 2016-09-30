#include "lightintensity.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <linux/i2c-dev.h>


LightIntensity &LightIntensity::instance()
{
    static LightIntensity m_lightIntensity;
    return m_lightIntensity;
}

int LightIntensity::intensity() const
{
    if(m_fd < 0)
        return 0;

    int iRes = 0;
    ::ioctl(m_fd, 21, &iRes);

    return iRes * 100 / 4095;
}

LightIntensity::LightIntensity() :
    m_fd(0)
{
    m_fd = open("/dev/lradc", 0);
}

LightIntensity::~LightIntensity()
{
    close(m_fd);
}
