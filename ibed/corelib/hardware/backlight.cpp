#include "backlight.h"
#include "systemcall.h"


Backlight::Backlight()
{

}


Backlight &Backlight::instance()
{
    static Backlight m_backlight;
    return m_backlight;
}

void Backlight::setValue(quint8 newValue)
{
    SystemCall::instance().cmd(QString("echo %1 > /sys/class/backlight/mxs-bl/brightness").arg(newValue));
}

void Backlight::setTurnOffTime(qint32 newTime)
{

}

quint8 Backlight::value()
{
    QString brightness;
    SystemCall::instance().cmd(QString("cat /sys/class/backlight/mxs-bl/brightness"), brightness);
    return brightness.toInt();
}

quint8 Backlight::maxValue()
{
    QString brightness;
    SystemCall::instance().cmd(QString("cat /sys/class/backlight/mxs-bl/max_brightness"), brightness);
    return brightness.toInt();
}

