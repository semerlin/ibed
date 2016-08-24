#include "kbdbacklight.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include "applogger.h"

KbdBacklight &KbdBacklight::instance()
{
    static KbdBacklight m_bkl;
    return m_bkl;
}

void KbdBacklight::turnOnBKL()
{
    char val = 1;
    if(::write(m_fd, &val, 1) < 0)
        AppLogger::instance().log()->error("turn on keyboard backlight failed.");
}

void KbdBacklight::turnOffBKL()
{
    char val = 0;
    if(::write(m_fd, &val, 1) < 0)
        AppLogger::instance().log()->error("turn on keyboard backlight failed.");
}

KbdBacklight::KbdBacklight() :
    m_fd(-1)
{
    m_fd = ::open("/dev/kbdbkl", O_WRONLY);
    if(m_fd == -1)
        AppLogger::instance().log()->error("init keyboard backlight control failed.");

    AppLogger::instance().log()->info("init keyboard backlight control success.");
}

KbdBacklight::~KbdBacklight()
{
    ::close(m_fd);
    m_fd = -1;
}


