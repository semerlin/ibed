#include "modulemanger.h"
#include "mainmodule.h"
#include "hardwaremodule.h"
#include "uimodule.h"
#include "thememodule.h"
#include "networkmodule.h"
#include "mediamodule.h"
#include "mainwidget.h"
#include "baseapplication.h"
#include "callmodule.h"
#include <QDebug>

MainModule::MainModule() :
    m_manger(new ModuleManger)
{
    //init modules
    m_manger->addModule(new UiModule("Ui"));
    m_manger->addModule(new ThemeModule("Theme"));
    m_manger->addModule(new HardwareModule("Hardware"));
    m_manger->addModule(new NetworkModule("Network"));
    m_manger->addModule(new MediaModule("Media"));
    m_manger->addModule(new CallModule("Call"));

}

bool MainModule::initialize()
{
    //modules
    UiModule *ui = m_manger->moduleConvert<UiModule>("Ui");
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");
    HardwareModule *hardware = m_manger->moduleConvert<HardwareModule>("Hardware");
    MediaModule *media = m_manger->moduleConvert<MediaModule>("Media");
    CallModule *call = m_manger->moduleConvert<CallModule>("Call");


    //connect signals
    QObject::connect(network, SIGNAL(registered()), ui, SLOT(onRegistered()));
    QObject::connect(network, SIGNAL(registerTimeout()), ui, SLOT(onRegisterTimeout()));
    QObject::connect(network, SIGNAL(disconnected()), ui, SLOT(onDisconnect()));
    QObject::connect(ui, SIGNAL(reconnect(QString, quint16)),
                     network, SLOT(reconnect(QString, quint16)));


    QObject::connect(network, SIGNAL(nameChanged(QString)), ui, SLOT(onNameChanged(QString)));
    QObject::connect(network, SIGNAL(sexChanged(QString)), ui, SLOT(onSexChanged(QString)));
    QObject::connect(network, SIGNAL(ageChanged(QString)), ui, SLOT(onAgeChanged(QString)));
    QObject::connect(network, SIGNAL(bedChanged(QString)), ui, SLOT(onBedChanged(QString)));
    QObject::connect(network, SIGNAL(levelChanged(QString)), ui, SLOT(onLevelChanged(QString)));
    QObject::connect(network, SIGNAL(timeChanged(QString)), ui, SLOT(onTimeChanged(QString)));
    QObject::connect(network, SIGNAL(doctorChanged(QString)), ui, SLOT(onDoctorChanged(QString)));
    QObject::connect(network, SIGNAL(eatChanged(QString)), ui, SLOT(onEatChanged(QString)));
    QObject::connect(network, SIGNAL(nurseChanged(QString)), ui, SLOT(onNurseChanged(QString)));
    QObject::connect(network, SIGNAL(adviseChanged(QString)), ui, SLOT(onAdviseChanged(QString)));
    QObject::connect(network, SIGNAL(allergyChanged(QString)), ui, SLOT(onAllergyChanged(QString)));

    QObject::connect(ui, SIGNAL(updateAdvise()), network, SLOT(getAdvise()));

    QObject::connect(network, SIGNAL(adviseUpdate(QString)), ui, SLOT(onAdviseUpdate(QString)));

    QObject::connect(ui, SIGNAL(uploadInOut(QStringList)), network, SLOT(uploadInOut(QStringList)));

#ifdef TARGET_IMX
    QObject::connect(ui, SIGNAL(brightnessChanged(int)), hardware, SLOT(setBrightness(int)));
    QObject::connect(ui, SIGNAL(turnOffTimeChanged(int)), hardware, SLOT(setTurnOffTime(int)));
#endif

    QObject::connect(ui, SIGNAL(play(QString)), media, SLOT(onPlay(QString)));
    QObject::connect(ui, SIGNAL(pause(QString)), media, SLOT(onPause(QString)));
    QObject::connect(ui, SIGNAL(stop(QString)), media, SLOT(onStop(QString)));

    QObject::connect(ui, SIGNAL(bedCtrlPressed(int)), this, SLOT(onBedControlPressed(int)));
    QObject::connect(ui, SIGNAL(bedCtrlReleased(int)), this, SLOT(onBedControlReleased(int)));

    connect(ui, SIGNAL(infuStart()), hardware, SLOT(startInfusion()));
    connect(ui, SIGNAL(infuStop()), hardware, SLOT(stopInfusion()));

    connect(ui, SIGNAL(infuStart()), this, SLOT(onInfuStart()));
    connect(ui, SIGNAL(infuStop()), this, SLOT(onInfuStop()));




#ifdef TARGET_IMX
    QObject::connect(hardware, SIGNAL(lightIntensityChanged(int)), ui, SLOT(onLightIntensityChanged(int)));
    QObject::connect(hardware, SIGNAL(temperatureChanged(int)), ui, SLOT(onTemperatureChanged(int)));
#endif

    connect(hardware, SIGNAL(weightChanged(double)), ui, SLOT(onWeightChanged(double)));
    connect(hardware, SIGNAL(infuCountChanged(int)), ui, SLOT(onInfuCountChanged(int)));
    connect(hardware, SIGNAL(infuMountChanged(int)), ui, SLOT(onInfuMountChanged(int)));
    connect(hardware, SIGNAL(infuSpeedChanged(int)), ui, SLOT(onInfuSpeedChanged(int)));

    connect(hardware, SIGNAL(infuSpeedChanged(int)), network, SLOT(sendInfuSpeed(int)));
    connect(hardware, SIGNAL(weightChanged(double)), network, SLOT(sendWeight(double)));

    QObject::connect(media, SIGNAL(intensityChanged(int)), ui, SLOT(onAudioIntensityChanged(int)));

    connect(call, SIGNAL(callOutConnecting()), ui, SLOT(onCallOutConnecting()));
    connect(call, SIGNAL(callOutConnected()), ui, SLOT(onCallOutConnected()));
    connect(call, SIGNAL(callOutLocalTerminate()), ui, SLOT(onCallOutTerminate()));
    connect(call, SIGNAL(callOutRemoteTerminate()), ui, SLOT(onCallOutTerminate()));

    connect(call, SIGNAL(callOutConnecting()), this, SLOT(onCallOutConnecting()));
    connect(call, SIGNAL(callOutConnected()), this, SLOT(onCallOutConnected()));
    connect(call, SIGNAL(callOutLocalTerminate()), this, SLOT(onCallOutTerminate()));
    connect(call, SIGNAL(callOutRemoteTerminate()), this, SLOT(onCallOutTerminate()));

    connect(this, SIGNAL(play(QString)), media, SLOT(onPlay(QString)));

    //connect app click signal
    BaseApplication *app = dynamic_cast<BaseApplication *>(qApp);
    if(app != NULL)
    {
        //stanbywidget control
        QObject::connect(app, SIGNAL(keyPressed(int)), ui, SLOT(onClicked()));
        QObject::connect(app, SIGNAL(mousePressed(const Qt::MouseButtons&)), ui, SLOT(onClicked()));

        //backlight control
        QObject::connect(app, SIGNAL(keyPressed(int)), hardware, SLOT(backlightOn()));
        QObject::connect(app, SIGNAL(mousePressed(const Qt::MouseButtons&)), hardware, SLOT(backlightOn()));
    }

    //show main widget
    if(ui != NULL)
    {
        ui->showMainWidget();
    }

    //connect to server
    network->init();

    //init media
    media->init();

    return true;
}

ModuleManger *MainModule::manger() const
{
    return m_manger;
}

void MainModule::onBedControlPressed(int id)
{
    HardwareModule *hardware = m_manger->moduleConvert<HardwareModule>("Hardware");

    switch(id)
    {
    case 1:
        hardware->motorMove(4, 1);
        break;
    case 2:
        hardware->motorMove(3, 1);
        break;
    case 3:
        hardware->motorMove(4, 2);
        break;
    case 4:
        hardware->motorMove(3, 2);
        break;
    case 5:
        hardware->motorMove(5, 1);
        break;
    case 7:
        hardware->motorMove(1, 1);
        break;
    case 8:
        hardware->motorMove(2, 1);
        break;
    case 10:
        hardware->motorMove(6, 2);
        break;
    case 11:
        hardware->motorMove(6, 1);
        break;
    case 12:
        hardware->motorMove(1, 2);
        break;
    case 13:
        hardware->motorMove(2, 2);
        break;
    case 15:
        hardware->motorMove(5, 2);
        break;
    default:
        break;
    }
}

void MainModule::onBedControlReleased(int id)
{
    HardwareModule *hardware = m_manger->moduleConvert<HardwareModule>("Hardware");

    switch(id)
    {
    case 1:
        hardware->motorMove(4, 0);
        break;
    case 2:
        hardware->motorMove(3, 0);
        break;
    case 3:
        hardware->motorMove(4, 0);
        break;
    case 4:
        hardware->motorMove(3, 0);
        break;
    case 5:
        hardware->motorMove(5, 0);
        break;
    case 7:
        hardware->motorMove(1, 0);
        break;
    case 8:
        hardware->motorMove(2, 0);
        break;
    case 10:
    case 11:
        hardware->motorMove(6, 0);
        break;
    case 12:
        hardware->motorMove(1, 0);
        break;
    case 13:
        hardware->motorMove(2, 0);
        break;
    case 15:
        hardware->motorMove(5, 0);
        break;
    default:
        break;
    }
}

void MainModule::onInfuStart()
{
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");
    network->sendInfuStatus(1);
}

void MainModule::onInfuStop()
{
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");
    network->sendInfuStatus(2);
}

void MainModule::onInfuMountChanged(int mount)
{
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");
    int left = (200 - mount) / 200;
    network->sendInfuLeft(left);
}

void MainModule::onCallOutConnecting()
{
    qDebug() << "play out music" ;
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");
    MediaModule *media = m_manger->moduleConvert<MediaModule>("Media");

//    emit play("./resource/audio/callout.wav");
//    media->onPlay("./resource/audio/callout.wav");
}

void MainModule::onCallOutConnected()
{
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");
    MediaModule *media = m_manger->moduleConvert<MediaModule>("Media");

    media->onStop("./resource/audio/callout.wav");
}

void MainModule::onCallOutTerminate()
{
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");
    MediaModule *media = m_manger->moduleConvert<MediaModule>("Media");

    media->onStop("./resource/audio/callout.wav");
}
