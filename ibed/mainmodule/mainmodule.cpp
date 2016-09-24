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
    connect(network, SIGNAL(registered()), ui, SLOT(onRegistered()));
    connect(network, SIGNAL(registerTimeout()), ui, SLOT(onRegisterTimeout()));
    connect(network, SIGNAL(disconnected()), ui, SLOT(onDisconnect()));
    connect(ui, SIGNAL(reconnect(QString,quint16,quint16,QString,QString,QString)),
                     network, SLOT(reconnect(QString,quint16,quint16,QString,QString,QString)));


    connect(network, SIGNAL(nameChanged(QString)), ui, SLOT(onNameChanged(QString)));
    connect(network, SIGNAL(sexChanged(QString)), ui, SLOT(onSexChanged(QString)));
    connect(network, SIGNAL(ageChanged(QString)), ui, SLOT(onAgeChanged(QString)));
    connect(network, SIGNAL(bedChanged(QString)), ui, SLOT(onBedChanged(QString)));
    connect(network, SIGNAL(levelChanged(QString)), ui, SLOT(onLevelChanged(QString)));
    connect(network, SIGNAL(timeChanged(QString)), ui, SLOT(onTimeChanged(QString)));
    connect(network, SIGNAL(doctorChanged(QString)), ui, SLOT(onDoctorChanged(QString)));
    connect(network, SIGNAL(eatChanged(QString)), ui, SLOT(onEatChanged(QString)));
    connect(network, SIGNAL(nurseChanged(QString)), ui, SLOT(onNurseChanged(QString)));
    connect(network, SIGNAL(adviseChanged(QString)), ui, SLOT(onAdviseChanged(QString)));
    connect(network, SIGNAL(allergyChanged(QString)), ui, SLOT(onAllergyChanged(QString)));
    connect(network, SIGNAL(motorMove(QMap<quint8,quint8>)),
            this, SLOT(onMotorMove(QMap<quint8,quint8>)));

    connect(ui, SIGNAL(updateAdvise()), network, SLOT(getAdvise()));

    connect(network, SIGNAL(adviseUpdate(QString)), ui, SLOT(onAdviseUpdate(QString)));

    connect(ui, SIGNAL(uploadInOut(QStringList)), network, SLOT(uploadInOut(QStringList)));

#ifdef TARGET_IMX
    connect(ui, SIGNAL(brightnessChanged(int)), hardware, SLOT(setBrightness(int)));
    connect(ui, SIGNAL(turnOffTimeChanged(int)), hardware, SLOT(setTurnOffTime(int)));
#endif

    connect(ui, SIGNAL(play(QString)), media, SLOT(onPlay(QString)));
    connect(ui, SIGNAL(pause(QString)), media, SLOT(onPause(QString)));
    connect(ui, SIGNAL(stop(QString)), media, SLOT(onStop(QString)));

    connect(ui, SIGNAL(bedCtrlPressed(int)), this, SLOT(onBedControlPressed(int)));
    connect(ui, SIGNAL(bedCtrlReleased(int)), this, SLOT(onBedControlReleased(int)));

    connect(ui, SIGNAL(infuStart()), hardware, SLOT(startInfusion()));
    connect(ui, SIGNAL(infuStop()), hardware, SLOT(stopInfusion()));

    connect(ui, SIGNAL(infuStart()), this, SLOT(onInfuStart()));
    connect(ui, SIGNAL(infuStop()), this, SLOT(onInfuStop()));


#ifdef TARGET_IMX
    connect(hardware, SIGNAL(lightIntensityChanged(int)), ui, SLOT(onLightIntensityChanged(int)));
    connect(hardware, SIGNAL(temperatureChanged(int)), ui, SLOT(onTemperatureChanged(int)));
    connect(hardware, SIGNAL(humidityChanged(int)), ui, SLOT(onHumidityChanged(int)));
#endif

    connect(hardware, SIGNAL(weightChanged(double)), ui, SLOT(onWeightChanged(double)));
    connect(hardware, SIGNAL(infuInputChanged(int)), ui, SLOT(onInfuInputChanged(int)));
    connect(hardware, SIGNAL(infuSpeedChanged(int)), ui, SLOT(onInfuSpeedChanged(int)));
    connect(hardware, SIGNAL(infuInputChanged(int)), this, SLOT(onInfuInputChanged(int)));
    connect(hardware, SIGNAL(infuSpeedChanged(int)), network, SLOT(sendInfuSpeed(int)));
    connect(hardware, SIGNAL(weightChanged(double)), network, SLOT(sendWeight(double)));

    connect(media, SIGNAL(intensityChanged(int)), ui, SLOT(onAudioIntensityChanged(int)));

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
        connect(app, SIGNAL(keyPressed(int)), ui, SLOT(onClicked()));
        connect(app, SIGNAL(mousePressed(const Qt::MouseButtons&)), ui, SLOT(onClicked()));

        //backlight control
        connect(app, SIGNAL(keyPressed(int)), hardware, SLOT(backlightOn()));
        connect(app, SIGNAL(mousePressed(const Qt::MouseButtons&)), hardware, SLOT(backlightOn()));
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
    case 6:
    {
        QMap<quint8, quint8> moves;
        moves[3] = 2;
        moves[4] = 1;
        moves[5] = 2;
        hardware->motorMove(moves);
        break;
    }
    case 7:
        hardware->motorMove(1, 1);
        break;
    case 8:
        hardware->motorMove(2, 1);
        break;
    case 9:
    {
        QMap<quint8, quint8> moves;
        moves[3] = 2;
        moves[4] = 2;
        moves[5] = 1;
        hardware->motorMove(moves);
        break;
    }
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

    //just stop all motors
    Q_UNUSED(id)
    hardware->motorMove(1, 0);
    hardware->motorMove(5, 0);
//    switch(id)
//    {
//    case 1:
//        hardware->motorMove(4, 0);
//        break;
//    case 2:
//        hardware->motorMove(3, 0);
//        break;
//    case 3:
//        hardware->motorMove(4, 0);
//        break;
//    case 4:
//        hardware->motorMove(3, 0);
//        break;
//    case 5:
//        hardware->motorMove(5, 0);
//        break;
//    case 6:
//    {
//        QMap<quint8, quint8> moves;
//        moves[3] = 0;
//        moves[4] = 0;
//        hardware->motorMove(moves);
//        break;
//    }
//    case 7:
//        hardware->motorMove(1, 0);
//        break;
//    case 8:
//        hardware->motorMove(2, 0);
//        break;
//    case 10:
//    case 11:
//        hardware->motorMove(6, 0);
//        break;
//    case 12:
//        hardware->motorMove(1, 0);
//        break;
//    case 13:
//        hardware->motorMove(2, 0);
//        break;
//    case 15:
//        hardware->motorMove(5, 0);
//        break;
//    default:
//        break;
//    }
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

void MainModule::onInfuInputChanged(int input)
{
    UiModule *ui = m_manger->moduleConvert<UiModule>("Ui");
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");

    if(ui->infuMount() > 0)
    {
        int left = (ui->infuMount() - input) * 100 / ui->infuMount();
        network->sendInfuLeft(left);
    }
}

void MainModule::onCallOutConnecting()
{
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");
    MediaModule *media = m_manger->moduleConvert<MediaModule>("Media");

//    media->onPlay("/ibed/resource/audio/callout.wav");
}

void MainModule::onCallOutConnected()
{
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");
    MediaModule *media = m_manger->moduleConvert<MediaModule>("Media");

//    media->onStop("/ibed/resource/audio/callout.wav");
}

void MainModule::onCallOutTerminate()
{
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");
    MediaModule *media = m_manger->moduleConvert<MediaModule>("Media");

//    media->onStop("/ibed/resource/audio/callout.wav");
}

void MainModule::onMotorMove(const QMap<quint8, quint8> &moves)
{
    HardwareModule *hardware = m_manger->moduleConvert<HardwareModule>("Hardware");
    QMap<quint8, quint8> motorMoves;
    quint8 id, dir;
    for(QMap<quint8, quint8>::const_iterator iter = moves.constBegin();
        iter != moves.constEnd(); ++iter)
    {
        id = iter.key();
        dir = iter.value();
        motorMoves.insert(id, dir);
    }

    hardware->motorMove(moves);
}

