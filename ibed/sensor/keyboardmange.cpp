#include <QTimer>
#include "keyboard.h"
#include "keyboardmange.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "boost/foreach.hpp"
#include <QSet>
#include "applogger.h"
#include <QDebug>


KeyboardMange::KeyboardMange() :
    m_fd(-1),
    m_monitor(new QTimer(this))
{
    m_monitor->setInterval(200);
    connect(m_monitor, SIGNAL(timeout()), this, SLOT(onMonitorKeys()));
}

KeyboardMange::~KeyboardMange()
{
    ::close(m_fd);
    delete(m_monitor);
    qDeleteAll(m_keyboards);
}

int KeyboardMange::init()
{
    m_fd = ::open("/dev/keybtn", O_RDONLY);
    if(m_fd < 0)
    {
        AppLogger::instance().log()->error("open keyboard button failed");
        return -1;
    }


//    for(int i = 0; i < 6; ++i)
//        m_allKeyId.append(i);

    addKeyboard(new Keyboard("/dev/i2c-1", 0x20));
    addKeyboard(new Keyboard("/dev/i2c-1", 0x21));

//    m_monitor->start();

    return 0;
}

void KeyboardMange::start()
{
    m_monitor->start();
}

void KeyboardMange::stop()
{
    m_monitor->stop();
}

QList<quint8> KeyboardMange::pressedKeys(int index)
{
    //judge range
    if(index >= m_keyboards.count())
        return QList<quint8>();

    return m_keyboards.at(index)->pressedKeys();
}

QList<quint8> KeyboardMange::releasedKeys(int index)
{
   //judge range
    if(index >= m_keyboards.count())
        return QList<quint8>();

    return m_keyboards.at(index)->releasedKeys();
}

void KeyboardMange::addKeyboard(Keyboard *keyboard)
{
    if(keyboard)
        m_keyboards.append(keyboard);
}

/* 应为和SHT20 公用 I2C1， 所以不能在这里面处理，会产生总线竞争 */
//void KeyboardMange::onMonitorKeys()
//{
//    if(m_fd >= 0)
//    {
//        int val;
//        ::read(m_fd, &val, 1);

//        if(val == 0)
//        {
//            //some key pressed
//            QSet<quint8> curPressedKeys;

//            BOOST_FOREACH(Keyboard *kbd, m_keyboards)
//            {
//                QList<quint8> pressedKeys = kbd->pressedKeys();

//                //press
//                foreach(const quint8 &id, pressedKeys)
//                    curPressedKeys.insert(id);
//            }

//            //start control
//            foreach(const quint8 &id, m_allKeyId)
//            {
//                //bed control
//                if(curPressedKeys.contains(id))
//                {
//                    emit keyPressed(id);
//                }
//                else
//                {
//                    emit keyReleased(id);
//                }
//            }
//        }

//    }
//}


void KeyboardMange::onMonitorKeys()
{
    if(m_fd > 0)
    {
        int val = 1;
        ::read(m_fd, &val, 1);

        if(val == 0)
        {
//            AppLogger::instance().log()->info("key pressed or released");
            emit keyStatusChanged();
        }

    }
}
