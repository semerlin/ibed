#include <QTimer>
#include "mainwidget.h"
#include "standbywidget.h"
#include "calldialog.h"
#include "progressdialog.h"
#include "numipmethod.h"
#include "uimodule.h"
#include <QResource>
#include <QApplication>

UiModule::UiModule(const QString &name) :
    BaseAppModule(name),
    m_standByTimer(new QTimer(this)),
    m_standByCount(0)
{
    m_standByTimer->setInterval(1000);
    connect(m_standByTimer, SIGNAL(timeout()), this, SLOT(onStandbyTimeout()));
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

    //register input method
#ifdef TARGET_IMX
    m_method = new NumIPMethod(m_mainWidget);
    m_method->setGeometry(0, 420, 800, 60);
    QWSServer::setCurrentInputMethod(m_method);
#endif

    //connect signals
    connect(m_mainWidget, SIGNAL(reconnect(QString, quint16)), this, SIGNAL(reconnect(QString, quint16)));
    connect(m_mainWidget, SIGNAL(updateAdvise()), this, SIGNAL(updateAdvise()));
    connect(m_mainWidget, SIGNAL(uploadInOut(QStringList)), this, SIGNAL(uploadInOut(QStringList)));
    connect(m_mainWidget, SIGNAL(brightnessChanged(int)), this, SIGNAL(brightnessChanged(int)));
    connect(m_mainWidget, SIGNAL(turnOffTimeChanged(int)), this, SIGNAL(turnOffTimeChanged(int)));
    connect(m_mainWidget, SIGNAL(play(QString)), this, SIGNAL(play(QString)));
    connect(m_mainWidget, SIGNAL(pause(QString)), this, SIGNAL(pause(QString)));
    connect(m_mainWidget, SIGNAL(stop(QString)), this, SIGNAL(stop(QString)));
    connect(m_mainWidget, SIGNAL(bedCtrlPressed(int)), this, SIGNAL(bedCtrlPressed(int)));
    connect(m_mainWidget, SIGNAL(bedCtrlReleased(int)), this, SIGNAL(bedCtrlReleased(int)));
    connect(m_mainWidget, SIGNAL(infuStart()), this, SIGNAL(infuStart()));
    connect(m_mainWidget, SIGNAL(infuStop()), this, SIGNAL(infuStop()));

    return true;
}

void UiModule::unload()
{
    delete m_standByTimer;
    delete m_progressDialog;
    delete m_callDialog;
    delete m_standbyWidget;
    delete m_mainWidget;
}

void UiModule::showMainWidget()
{
    m_mainWidget->show();
    m_standByTimer->start();
}

int UiModule::infuMount() const
{
    return m_mainWidget->infuMount();
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
    m_standbyWidget->setName(name);
}

void UiModule::onSexChanged(const QString &sex)
{
    m_mainWidget->setSex(sex);
}

void UiModule::onAgeChanged(const QString &age)
{
    m_mainWidget->setAge(age);
    m_standbyWidget->setAge(age.toInt());
}

void UiModule::onBedChanged(const QString &bed)
{
    m_mainWidget->setBed(bed);
    m_standbyWidget->setBedNum(bed.toInt());
}

void UiModule::onLevelChanged(const QString &level)
{
    m_mainWidget->setLevel(level);
    m_standbyWidget->setNursery(level.toInt());
}

void UiModule::onTimeChanged(const QString &time)
{
    int index = time.indexOf("/");
    m_mainWidget->setTime(time.left(index) + "\n" + time.right(time.count() - index - 1));
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

void UiModule::onAdviseUpdate(const QString &data)
{
    m_mainWidget->addAdvise(data);
}

void UiModule::onStandbyTimeout()
{
    if(m_standByCount++ > 6)
    {
        if(m_standbyWidget->isHidden())
            m_standbyWidget->show();
    }
}

void UiModule::onStandbyClicked()
{
    m_standByCount = 0;
    m_standbyWidget->hide();
}

void UiModule::onLightIntensityChanged(int intensity)
{
    m_standbyWidget->setLightIntensity(QString::number(intensity));
}

void UiModule::onTemperatureChanged(int temper)
{
    m_standbyWidget->setTemperature(QString::number(temper)+"℃");
}

void UiModule::onHumidityChanged(int humidity)
{
    m_standbyWidget->setHumidity(QString::number(humidity) + "%");
}

void UiModule::onAudioIntensityChanged(int intensity)
{
    m_standbyWidget->setAudioIntensity(QString::number(intensity));
}

void UiModule::onClicked()
{
    m_standByCount = 0;
    if(!m_standbyWidget->isHidden())
        m_standbyWidget->hide();
}

void UiModule::onWeightChanged(double weight)
{
    int temp = static_cast<int>(weight);
    m_standbyWidget->setWeight(QString::number(temp)+"Kg");
    m_mainWidget->setWeight(weight);
}

void UiModule::onInfuInputChanged(int mount)
{
    if(m_mainWidget->infuMount() > 0)
    {
        int left = (m_mainWidget->infuMount() - mount) / m_mainWidget->infuMount();
        m_mainWidget->setLeft(left);
    }
}


void UiModule::onInfuSpeedChanged(int speed)
{
    m_mainWidget->setSpeed(speed);
}

void UiModule::onCallOutConnecting()
{
    m_callDialog->show();
}

void UiModule::onCallOutConnected()
{

}

void UiModule::onCallOutTerminate()
{
    m_callDialog->hide();
}
