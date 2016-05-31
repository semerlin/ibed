#include "hardwaremodule.h"
#include "powermange.h"
#include "backlight.h"
#include "serialportctrl.h"

HardwareModule::HardwareModule()
{

}

HardwareModule &HardwareModule::instance()
{
    static HardwareModule m_hardware;
    return m_hardware;
}

bool HardwareModule::load(const QVariant &val)
{
    emit message(tr("init hardware..."));
    /*****backlight****/
    //set backlight to max brightness
    emit message(tr(""));
    Backlight::instance().setValue(Backlight::instance().maxValue());
    //serial

    /****powermange****/
    //init power mangement unit
    emit message(tr(""));
    PowerMange::instance().setIdleInterval(10);
    PowerMange::instance().setSuspendInterval(20);
    PowerMange::instance().addDevice(&Backlight::instance());
    PowerMange::instance().run();
}

void HardwareModule::unload()
{
    PowerMange::instance().stop();
    PowerMange::instance().removeAllDevices();
}

