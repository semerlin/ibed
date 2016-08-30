#include <QTimer>
#include "sht20.h"
#include "keyboardmange.h"
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
#include "ledintensity.h"
#include "kbdbacklight.h"

HardwareModule::HardwareModule(const QString &name) :
    BaseAppModule(name),
    m_lightIntensity(0),
    m_temper(0),
    m_humidity(0)
{
#ifdef TARGET_IMX
    m_i2cMutex = new QMutex;
    m_sht20 = new SHT20("/dev/i2c-1", 0x40);
    m_kbdMange = new KeyboardMange;
    connect(m_kbdMange, SIGNAL(keyStatusChanged()), this, SLOT(onKeyStatusChanged()));
#endif

    m_lightTimer = new QTimer(this);
    m_lightTimer->setInterval(1000);
    connect(m_lightTimer, SIGNAL(timeout()), this, SLOT(updateLightIntensity()));

    m_temperTimer = new QTimer(this);
    m_temperTimer->setInterval(1000);
    connect(m_temperTimer, SIGNAL(timeout()), this, SLOT(updateTemper()));

    m_infuTimer = new QTimer(this);
    m_infuTimer->setInterval(1000);
    connect(m_infuTimer, SIGNAL(timeout()), this, SLOT(updateInfusion()));

    m_weightTimer = new QTimer(this);
    m_weightTimer->setInterval(1000);
    connect(m_weightTimer, SIGNAL(timeout()), this, SLOT(updateWeight()));


}

HardwareModule::~HardwareModule()
{
    delete m_lightTimer;
    delete m_temperTimer;
    delete m_sht20;
    delete m_infuTimer;
    delete m_weightTimer;
}


bool HardwareModule::load(const QVariant &val)
{
    Q_UNUSED(val)

#ifdef TARGET_IMX
    //load drivers
    loadDrivers();

    connect(&BedControl::instance(), SIGNAL(weightChanged(double)), this, SIGNAL(weightChanged(double)));
    connect(&BedControl::instance(), SIGNAL(infuCountChanged(int)), this, SIGNAL(infuCountChanged(int)));
    connect(&BedControl::instance(), SIGNAL(infuMountChanged(int)), this, SIGNAL(infuMountChanged(int)));
    connect(&BedControl::instance(), SIGNAL(infuSpeedChanged(int)), this, SIGNAL(infuSpeedChanged(int)));
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

    //start keyboard monitor
    m_kbdMange->init();
    m_kbdMange->start();

    //turn off keyboard backlight
    KbdBacklight::instance().turnOffBKL();

#endif

    BedControl::instance().powerOn();

    //start weight timer
    m_weightTimer->start();

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

void HardwareModule::motorMove(int id, int dir)
{
    BedControl::MotorDirection direction;
    switch(dir)
    {
    case 0:
        //stop
        direction = BedControl::Stop;
        break;
    case 1:
        direction = BedControl::Forword;
        break;
    case 2:
        direction = BedControl::Reversal;
        break;
    default:
        direction = BedControl::Stop;
        break;
    }

    BedControl::instance().motorMove(id, direction);
}

void HardwareModule::motorMove(const QList<int> id, int dir)
{
    BedControl::MotorDirection direction;
    switch(dir)
    {
    case 0:
        //stop
        direction = BedControl::Stop;
        break;
    case 1:
        direction = BedControl::Forword;
        break;
    case 2:
        direction = BedControl::Reversal;
        break;
    default:
        direction = BedControl::Stop;
        break;
    }

    BedControl::instance().motorMove(id, direction);
}

void HardwareModule::startInfusion()
{
    AppLogger::instance().log()->info("start infusion monitor");
    m_infuTimer->start();
}

void HardwareModule::stopInfusion()
{
    AppLogger::instance().log()->info("stop infusion monitor");
    m_infuTimer->stop();
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
    m_i2cMutex->lock();
    int temp = m_sht20->temperature();
    m_i2cMutex->unlock();
    if(temp != m_temper)
    {
        AppLogger::instance().log()->debug(QString("temperature changed to: %1").arg(m_temper));
        m_temper = temp;
        emit temperatureChanged(m_temper);
    }

    m_i2cMutex->lock();
    int hum = m_sht20->humidity();
    m_i2cMutex->unlock();
    if(hum != m_humidity)
    {
        AppLogger::instance().log()->debug(QString("humidity changed to: %1").arg(m_humidity));
        m_humidity = hum;
        emit humidityChanged(m_humidity);
    }

#endif
}

void HardwareModule::updateInfusion()
{
    BedControl::instance().getInfusionCount();
//    BedControl::instance().getInfusionMount();
//    BedControl::instance().getInfusionSpeed();
}

void HardwareModule::updateWeight()
{
    BedControl::instance().getWeight();
}

void HardwareModule::onKeyStatusChanged()
{
#ifdef TARGET_IMX
    m_i2cMutex->lock();
    QList<quint8> kbd0PressedKeys = m_kbdMange->pressedKeys(0);
    QList<quint8> kbd0ReleasedKeys = m_kbdMange->releasedKeys(0);
    QList<quint8> kbd1PressedKeys = m_kbdMange->pressedKeys(1);
    QList<quint8> kbd1ReleasedKeys = m_kbdMange->releasedKeys(1);
    m_i2cMutex->unlock();

    //just support one press a time

    //process kbd1
    if(kbd0PressedKeys.count() > 0)
    {
        switch(kbd0PressedKeys.at(0))
        {
        case 2:
            BedControl::instance().motorMove(3, BedControl::Reversal);
            break;
        case 3:
            BedControl::instance().motorMove(4, BedControl::Reversal);
            break;
        case 4:
            BedControl::instance().motorMove(4, BedControl::Forword);
            break;
        case 5:
            BedControl::instance().motorMove(3, BedControl::Forword);
            break;
        default:
            break;
        }
    }
    else
    {

        foreach(const quint8 &id, kbd0ReleasedKeys)
        {
            switch(id)
            {
            case 2:
                BedControl::instance().motorMove(3, BedControl::Stop);
                break;
            case 3:
                BedControl::instance().motorMove(4, BedControl::Stop);
                break;
            case 4:
                BedControl::instance().motorMove(4, BedControl::Stop);
                break;
            case 5:
                BedControl::instance().motorMove(3, BedControl::Stop);
                break;
            default:
                break;
            }
        }

    }


    //process kbd2
    if(kbd0PressedKeys.count() > 0)
        return ;

    if(kbd1PressedKeys.count() > 0)
    {
        switch(kbd1PressedKeys.at(0))
        {
        case 2:
            BedControl::instance().motorMove(3, BedControl::Forword);
            break;
        case 3:
            BedControl::instance().motorMove(4, BedControl::Forword);
            break;
        case 4:
            BedControl::instance().motorMove(4, BedControl::Reversal);
            break;
        case 5:
            BedControl::instance().motorMove(3, BedControl::Reversal);
            break;
        default:
            break;
        }
    }
    else
    {

        foreach(const quint8 &id, kbd1ReleasedKeys)
        {
            switch(id)
            {
            case 2:
                BedControl::instance().motorMove(3, BedControl::Stop);
                break;
            case 3:
                BedControl::instance().motorMove(4, BedControl::Stop);
                break;
            case 4:
                BedControl::instance().motorMove(4, BedControl::Stop);
                break;
            case 5:
                BedControl::instance().motorMove(3, BedControl::Stop);
                break;
            default:
                break;
            }
        }

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
        QFile file(QString("/dev/%1").arg(info.baseName()));
        if(!file.exists())
        {
            SystemCall::instance().cmd("insmod " + info.absoluteFilePath());
            AppLogger::instance().log()->info(QString("load driver: %1").arg(info.fileName()));
        }
    }
#endif
}







