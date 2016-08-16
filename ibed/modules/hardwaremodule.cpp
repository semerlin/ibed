#include <QTimer>
#include "hardwaremodule.h"
#include "powermange.h"
#include "backlight.h"
#include "serialportctrl.h"
#include "applogger.h"
#include <QDebug>
#include "appsetting.h"
#include "powercontrol.h"
#include "appsetting.h"
#include "systemcall.h"
#include <QDir>
#include <QDirIterator>
#include "lightintensity.h"

HardwareModule::HardwareModule(const QString &name) :
    BaseAppModule(name),
    m_lightIntensity(0)
{
    m_lightTimer = new QTimer(this);
    m_lightTimer->setInterval(1000);
    connect(m_lightTimer, SIGNAL(timeout()), this, SLOT(updateLightIntensity()));
}

HardwareModule::~HardwareModule()
{
}


bool HardwareModule::load(const QVariant &val)
{
    Q_UNUSED(val)

#ifdef TARGET_IMX
    //load drivers
    loadDrivers();
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

    //enable speaker
    PowerControl::instance().spkEnable(true);

    //start intensity timer
    m_lightTimer->start();
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

void HardwareModule::updateLightIntensity()
{
#ifdef TARGET_IMX
    int temp = LightIntensity::instance().intensity();
    if(temp != m_lightIntensity)
    {
        AppLogger::instance().log()->debug(QString("intensity changed to: %1").arg(m_lightIntensity));
        m_lightIntensity = temp;
        emit lightIntensityChanged(m_lightIntensity);
    }
#endif
}

void HardwareModule::loadDrivers()
{
#ifdef TARGET_IMX
    QString driverFolder = AppSetting::instance().value(AppSetting::DriverConfig).toString();

    QDir dir(driverFolder);
    if(!dir.exists())
        return;

    QStringList filters;
    filters << QString("*.ko");

    QDirIterator dirIter(driverFolder, filters,
                         QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot,
                         QDirIterator::Subdirectories);

    while(dirIter.hasNext())
    {
        dirIter.next();
        QFileInfo info = dirIter.fileInfo();
        SystemCall::instance().cmd("insmod " + info.absoluteFilePath());
        AppLogger::instance().log()->info(QString("load driver: %1").arg(info.fileName()));
    }
#endif
}

