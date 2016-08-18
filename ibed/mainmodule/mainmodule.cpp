#include "modulemanger.h"
#include "mainmodule.h"
#include "hardwaremodule.h"
#include "uimodule.h"
#include <QObject>
#include "thememodule.h"
#include "networkmodule.h"
#include "mediamodule.h"
#include "mainwidget.h"
#include "baseapplication.h"

MainModule::MainModule() :
    m_manger(new ModuleManger)
{
    //init modules
    m_manger->addModule(new UiModule("Ui"));
    m_manger->addModule(new ThemeModule("Theme"));
    m_manger->addModule(new HardwareModule("Hardware"));
    m_manger->addModule(new NetworkModule("Network"));
    m_manger->addModule(new MediaModule("Media"));

}

bool MainModule::initialize()
{
    //modules
    UiModule *ui = m_manger->moduleConvert<UiModule>("Ui");
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");
    HardwareModule *hardware = m_manger->moduleConvert<HardwareModule>("Hardware");
    MediaModule *media = m_manger->moduleConvert<MediaModule>("Media");

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

    QObject::connect(ui, SIGNAL(brightnessChanged(int)), hardware, SLOT(setBrightness(int)));
    QObject::connect(ui, SIGNAL(turnOffTimeChanged(int)), hardware, SLOT(setTurnOffTime(int)));

    QObject::connect(ui, SIGNAL(play(QString)), media, SLOT(onPlay(QString)));
    QObject::connect(ui, SIGNAL(pause(QString)), media, SLOT(onPause(QString)));
    QObject::connect(ui, SIGNAL(stop(QString)), media, SLOT(onStop(QString)));

    QObject::connect(hardware, SIGNAL(lightIntensityChanged(int)), ui, SLOT(onLightIntensityChanged(int)));

    QObject::connect(media, SIGNAL(intensityChanged(int)), ui, SLOT(onAudioIntensityChanged(int)));

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
