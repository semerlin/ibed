#include "mainwidget.h"
#include "standbywidget.h"
#include "calldialog.h"
#include "progressdialog.h"
#include "uimodule.h"
#include <QResource>

UiModule::UiModule(const QString &name) :
    BaseAppModule(name)
{

}

UiModule::~UiModule()
{
    unload();
}

bool UiModule::load(const QVariant &val)
{
    Q_UNUSED(val)
    //register resource
    QResource::registerResource("./resource/ui/res.rcc");


    m_mainWidget =new MainWidget;
    m_standbyWidget =new StandbyWidget;
    m_callDialog =new CallDialog;
    m_progressDialog =new ProgressDialog;

    //connect signals
    connect(m_mainWidget, SIGNAL(reconnect(QString, quint16)), this, SIGNAL(reconnect(QString, quint16)));

    return true;
}

void UiModule::unload()
{
    delete m_progressDialog;
    delete m_callDialog;
    delete m_standbyWidget;
    delete m_mainWidget;
}

void UiModule::showMainWidget()
{
    m_mainWidget->show();
}

void UiModule::onRegistered()
{
    m_mainWidget->setNetworkStatus(QT_TRANSLATE_NOOP("Server", "连接成功!"));
}

void UiModule::onRegisterTimeout()
{
    m_mainWidget->setNetworkStatus(QT_TRANSLATE_NOOP("Server", "连接失败!"));
}

void UiModule::onDisconnect()
{
    m_mainWidget->setNetworkStatus(QT_TRANSLATE_NOOP("Server", "连接失败!"));
}

void UiModule::onNameChanged(const QString &name)
{
    m_mainWidget->setName(name);
}

void UiModule::onSexChanged(const QString &sex)
{
    m_mainWidget->setSex(sex);
}

void UiModule::onAgeChanged(const QString &age)
{
    m_mainWidget->setAge(age);
}

void UiModule::onBedChanged(const QString &bed)
{
    m_mainWidget->setBed(bed);
}

void UiModule::onLevelChanged(const QString &level)
{
    m_mainWidget->setLevel(level);
}

void UiModule::onTimeChanged(const QString &time)
{
    m_mainWidget->setTime(time);
}

void UiModule::onDoctorChanged(const QString &doctor)
{
    m_mainWidget->setDoctor(doctor);
}

void UiModule::onEatChanged(const QString &eat)
{
    m_mainWidget->setEat(eat);
}

void UiModule::onNurseChanged(const QString &nurse)
{
    m_mainWidget->setNurse(nurse);
}

void UiModule::onAdviseChanged(const QString &advise)
{
    m_mainWidget->setAdvise(advise);
}

void UiModule::onAllergyChanged(const QString &allergy)
{
    m_mainWidget->setAllergy(allergy);
}
