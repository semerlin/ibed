#include "hardwaremodule.h"
#include "powermange.h"
#include "backlight.h"
#include "serialportctrl.h"
#include "applogger.h"


HardwareModule::HardwareModule(const QString &name) :
    BaseAppModule(name)
{

}

HardwareModule::~HardwareModule()
{
    emit deleted();
}


HardwareModule &HardwareModule::instance()
{
    static HardwareModule m_hardware("Hardware");
    return m_hardware;
}

bool HardwareModule::load(const QVariant &val)
{
    Q_UNUSED(val)

    AppLogger::instance().log()->debug("hardware");
    emit message(tr("init hardware..."));
    /*****backlight****/
    //set backlight to max brightness
    emit message(tr("aaaaaa"));
//    Backlight::instance().setValue(Backlight::instance().maxValue());
    //serial

    /****powermange****/
    //init power mangement unit
    emit message(tr("bbbbbb"));
//    PowerMange::instance().setIdleInterval(10);
//    PowerMange::instance().setSuspendInterval(20);
//    PowerMange::instance().addDevice(&Backlight::instance());
//    PowerMange::instance().run();

    m_isLoaded = true;

    sleep(3);

    return true;
}

void HardwareModule::unload()
{
//    PowerMange::instance().stop();
//    PowerMange::instance().removeAllDevices();
    m_isLoaded = false;
}

