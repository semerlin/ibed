#include "modulemanger.h"
#include "mainmodule.h"
#include "hardwaremodule.h"
#include "uimodule.h"
#include <QObject>
#include "thememodule.h"
#include "networkmodule.h"
#include "mainwidget.h"

MainModule::MainModule() :
    m_manger(new ModuleManger)
{
    //init modules
    m_manger->addModule(new UiModule("Ui"));
    m_manger->addModule(new ThemeModule("Theme"));
    m_manger->addModule(new HardwareModule("Hardware"));
    m_manger->addModule(new NetworkModule("Network"));

}

bool MainModule::initialize()
{
    //modules
    UiModule *ui = m_manger->moduleConvert<UiModule>("Ui");
    NetworkModule *network = m_manger->moduleConvert<NetworkModule>("Network");

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
    QObject::connect(network, SIGNAL(doctorChanged(QString)), ui, SLOT(onDoctorChanged(QString)));
    QObject::connect(network, SIGNAL(eatChanged(QString)), ui, SLOT(onEatChanged(QString)));
    QObject::connect(network, SIGNAL(nurseChanged(QString)), ui, SLOT(onNurseChanged(QString)));
    QObject::connect(network, SIGNAL(adviseChanged(QString)), ui, SLOT(onAdviseChanged(QString)));
    QObject::connect(network, SIGNAL(allergyChanged(QString)), ui, SLOT(onAllergyChanged(QString)));

    //show main widget
    if(ui != NULL)
    {
        ui->showMainWidget();
    }

    //connect to server
    network->init();

    return true;
}

ModuleManger *MainModule::manger() const
{
    return m_manger;
}
