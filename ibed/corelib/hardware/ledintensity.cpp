#include "ledintensity.h"
#include "systemcall.h"


LedIntensity::LedIntensity()
{
    value();
}



LedIntensity &LedIntensity::instance()
{
    static LedIntensity m_led;
    return m_led;
}


QString LedIntensity::name() const
{
    return "LED";
}

void LedIntensity::setValue(quint8 newValue)
{
    if(m_curVal != newValue)
    {
        quint8 prevVal = m_curVal;
        m_curVal = newValue;
        SystemCall::instance().cmd(QString("echo %1 > /sys/class/leds/led-pwm4/brightness").arg(newValue));

        emit brightnessChanged(prevVal, m_curVal);
    }
}


quint8 LedIntensity::value()
{
    QString brightness;
    SystemCall::instance().cmd(QString("cat /sys/class/leds/led-pwm4/brightness"), brightness);
    m_curVal = brightness.toInt();
    return m_curVal;
}

quint8 LedIntensity::maxValue()
{
    QString brightness;
    SystemCall::instance().cmd(QString("cat /sys/class/leds/led-pwm4/brightness"), brightness);
    return brightness.toInt();
}

void LedIntensity::autoSetValue(quint8 value)
{
    QString brightness;
    SystemCall::instance().cmd(QString("cat /sys/class/leds/led-pwm4/brightness"), brightness);
    quint8 prevVal = brightness.toInt();

    SystemCall::instance().cmd(QString("echo %1 > /sys/class/leds/led-pwm4/brightness").arg(value));
    emit brightnessChanged(prevVal, value);
}


void LedIntensity::EnterState(POWER_STATE state)
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

bool LedIntensity::isReadable() const
{
    return true;
}

bool LedIntensity::isWriteable() const
{
    return true;
}

bool LedIntensity::isReadonly() const
{
   return false;
}

