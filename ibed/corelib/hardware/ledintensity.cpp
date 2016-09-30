#include "ledintensity.h"
#include "systemcall.h"


LedIntensity::LedIntensity() :
    m_prevVal(100),
    m_onVal(100)
{
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
    if(m_onVal != newValue)
    {
        quint8 prevVal = m_prevVal;
        m_onVal = newValue;
//        SystemCall::system(QString("echo %1 > /sys/class/leds/led-pwm4/brightness").arg(newValue));

        emit brightnessChanged(prevVal, m_onVal);
    }
}


quint8 LedIntensity::value()
{
    QString brightness;
//    SystemCall::getCmdOut(QString("cat /sys/class/leds/led-pwm4/brightness"), brightness);
    return brightness.toInt();
}

quint8 LedIntensity::maxValue()
{
    QString brightness;
//    SystemCall::getCmdOut(QString("cat /sys/class/leds/led-pwm4/brightness"), brightness);
    return brightness.toInt();
}

void LedIntensity::autoSetValue(quint8 value)
{
    quint8 prevVal = m_prevVal;

//    SystemCall::system(QString("echo %1 > /sys/class/leds/led-pwm4/brightness").arg(value));
    m_prevVal = value;
    emit brightnessChanged(prevVal, value);
}


void LedIntensity::EnterState(POWER_STATE state)
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

