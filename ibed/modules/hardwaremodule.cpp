#include "hardwaremodule.h"
#include "powermange.h"
#include "backlight.h"
#include "serialportctrl.h"
#include "applogger.h"
#include <QDebug>
#include "appsetting.h"

HardwareModule::HardwareModule(const QString &name) :
    BaseAppModule(name)
{

}

HardwareModule::~HardwareModule()
{
}


bool HardwareModule::load(const QVariant &val)
{
    Q_UNUSED(val)

#ifdef TARGET_IMX
//    AppLogger::instance().log()->debug("hardware");
//    emit message(tr("init hardware..."));
    /*****backlight****/
    //set backlight to max brightness
//    emit message(tr("aaaaaa"));
    Backlight::instance().setValue(AppSetting::instance().value(AppSetting::Brightness).toInt());
    //serial

    /****powermange****/
    //init power mangement unit
//    emit message(tr("bbbbbb"));
    int time = AppSetting::instance().value(AppSetting::TurnOffTime).toInt();
    if(time >= 5)
    {
        PowerMange::instance().setIdleInterval(time * 2 / 3);
        PowerMange::instance().setSuspendInterval(time * 1 / 3);
        PowerMange::instance().addDevice(&Backlight::instance());
        PowerMange::instance().run();
    }

#endif

    m_isLoaded = true;

//    sleep(2);
    return true;
}

void HardwareModule::unload()
{
#ifdef TARGET_IMX
    PowerMange::instance().stop();
    PowerMange::instance().removeAllDevices();
#endif
    m_isLoaded = false;
}

void HardwareModule::backlightOn()
{
#ifdef TARGET_IMX
    PowerMange::instance().powerOn();
#endif
}

void HardwareModule::setBrightness(int value)
{
#ifdef TARGET_IMX
    Backlight::instance().setValue(value);
#endif
}

void HardwareModule::setTurnOffTime(int value)
{
#ifdef TARGET_IMX
    if(value >= 5)
    {
        PowerMange::instance().setIdleInterval(value * 2 / 3);
        PowerMange::instance().setSuspendInterval(value * 1 / 3);
        PowerMange::instance().addDevice(&Backlight::instance());
        PowerMange::instance().run();
    }
    else
    {
        PowerMange::instance().stop();
    }
#endif
}

