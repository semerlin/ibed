#include "backlight.h"
#include "systemcall.h"


Backlight::Backlight()
{
    value();
}



Backlight &Backlight::instance()
{
    static Backlight m_backlight;
    return m_backlight;
}


QString Backlight::name() const
{
    return "BKL";
}

void Backlight::setValue(quint8 newValue)
{
    if(m_curVal != newValue)
    {
        quint8 prevVal = m_curVal;
        m_curVal = newValue;
        SystemCall::instance().cmd(QString("echo %1 > /sys/class/backlight/mxs-bl/brightness").arg(newValue));

        emit brightnessChanged(prevVal, m_curVal);
    }
}


quint8 Backlight::value()
{
    QString brightness;
    SystemCall::instance().cmd(QString("cat /sys/class/backlight/mxs-bl/brightness"), brightness);
    m_curVal = brightness.toInt();
    return m_curVal;
}

quint8 Backlight::maxValue()
{
    QString brightness;
    SystemCall::instance().cmd(QString("cat /sys/class/backlight/mxs-bl/max_brightness"), brightness);
    return brightness.toInt();
}

void Backlight::autoSetValue(quint8 value)
{
    QString brightness;
    SystemCall::instance().cmd(QString("cat /sys/class/backlight/mxs-bl/max_brightness"), brightness);
    quint8 prevVal = brightness.toInt();

    SystemCall::instance().cmd(QString("echo %1 > /sys/class/backlight/mxs-bl/brightness").arg(value));
    emit brightnessChanged(prevVal, value);
}


void Backlight::EnterState(POWER_STATE state)
{
   if(state == POWER_ON)
   {
        autoSetValue(m_curVal);
   }
   else if(state == POWER_IDLE)
   {
        autoSetValue(m_curVal / 2);
   }
   else if(state == POWER_SUSPEND)
   {
        autoSetValue(0);
   }
   else
       return ;
}

bool Backlight::isReadable() const
{
    return true;
}

bool Backlight::isWriteable() const
{
    return true;
}

bool Backlight::isReadonly() const
{
   return false;
}

