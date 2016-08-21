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
#include "bedcontrol.h"
#include "sht20.h"
#include "ledintensity.h"

HardwareModule::HardwareModule(const QString &name) :
    BaseAppModule(name),
    m_lightIntensity(0),
    m_temper(0),
    m_humidity(0)
{
    m_lightTimer = new QTimer(this);
    m_lightTimer->setInterval(1000);
    connect(m_lightTimer, SIGNAL(timeout()), this, SLOT(updateLightIntensity()));

    m_temperTimer = new QTimer(this);
    m_temperTimer->setInterval(1000);
    connect(m_temperTimer, SIGNAL(timeout()), this, SLOT(updateTemper()));
}

HardwareModule::~HardwareModule()
{
    delete m_lightTimer;
    delete m_temperTimer;
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
    LedIntensity::instance().setValue(AppSetting::instance().value(AppSetting::Brightness).toInt() * 2);
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
        PowerMange::instance().addDevice(&LedIntensity::instance());
        PowerMange::instance().run();
    }

    //enable speaker
    PowerControl::instance().spkEnable(true);

    //turn on external 12v power
    PowerControl::instance().externalPowerOn(true);

    //start intensity timer
    m_lightTimer->start();

    //start temper timer
    m_temperTimer->start();

#endif

//    BedControl::instance().powerOn();


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
    LedIntensity::instance().setValue(value * 2);
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
        PowerMange::instance().addDevice(&LedIntensity::instance());
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

void HardwareModule::updateTemper()
{
#ifdef TARGET_IMX
    int temp = SHT20::temperature();
    if(temp != m_temper)
    {
        AppLogger::instance().log()->debug(QString("temperature changed to: %1").arg(m_temper));
        m_temper = temp;
        emit temperatureChanged(m_temper);
    }

    int hum = SHT20::humidity();
    if(hum != m_humidity)
    {
        AppLogger::instance().log()->debug(QString("humidity changed to: %1").arg(m_humidity));
        m_humidity = hum;
        emit humidityChanged(m_humidity);
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

