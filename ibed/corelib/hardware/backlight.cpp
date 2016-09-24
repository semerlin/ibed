#include "backlight.h"
#include "systemcall.h"


Backlight::Backlight() :
    m_onVal(100),
    m_prevVal(100)
{
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
    if(m_onVal != newValue)
    {
        quint8 prevVal = m_prevVal;
        m_onVal = newValue;
        SystemCall::system(QString("echo %1 > /sys/class/backlight/mxs-bl/brightness").arg(newValue));

        emit brightnessChanged(prevVal, m_onVal);
    }
}


quint8 Backlight::value()
{
    QString brightness;
    SystemCall::getCmdOut(QString("cat /sys/class/backlight/mxs-bl/brightness"), brightness);
    return brightness.toInt();
}

quint8 Backlight::maxValue()
{
    QString brightness;
    SystemCall::getCmdOut(QString("cat /sys/class/backlight/mxs-bl/max_brightness"), brightness);
    return brightness.toInt();
}

void Backlight::autoSetValue(quint8 value)
{
    quint8 prevVal = m_prevVal;

    SystemCall::system(QString("echo %1 > /sys/class/backlight/mxs-bl/brightness").arg(value));
    m_prevVal = value;
    emit brightnessChanged(prevVal, value);
}


void Backlight::EnterState(POWER_STATE state)
{
   if(state == POWER_ON)
   {
        autoSetValue(m_onVal);
   }
   else if(state == POWER_IDLE)
   {
        autoSetValue(m_onVal / 2);
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

