#include <QTimer>
#include "callbtn.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "applogger.h"
#include "log4qt/logger.h"


CallBtn::CallBtn() :
    m_fd(-1),
    m_timer(new QTimer(this))
{
    m_timer->setInterval(500);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onMonitorKeys()));
}

CallBtn::~CallBtn()
{
    delete m_timer;
    ::close(m_fd);
}

bool CallBtn::init()
{
    m_fd = ::open("/dev/callbtn", O_RDONLY);
    if(m_fd < 0)
    {
        AppLogger::instance().log()->error("open call button failed");
        return false;
    }
    AppLogger::instance().log()->info("open call button success");

    m_timer->start();

    return true;
}

void CallBtn::onMonitorKeys()
{
    if(m_fd > 0)
    {
        char val = 0;
        if(::read(m_fd, &val, 1) != -1)
        {
            if(val == 1)
            {
                emit callPressed();
            }
            else if(val == 2)
            {
                emit cancelPressed();
            }
        }
    }
}

