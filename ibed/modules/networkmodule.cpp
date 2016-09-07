#include "defaultclient.h"
#include "registerdatahandler.h"
#include "networkmodule.h"
#include "servermanger.h"

NetworkModule::NetworkModule(const QString &name) :
    BaseAppModule(name)
{

}

NetworkModule::~NetworkModule()
{
    unload();
}

bool NetworkModule::load(const QVariant &val)
{
    Q_UNUSED(val)

    m_defaultClient = new DefaultClient;

    connect(m_defaultClient, SIGNAL(registered()), this, SIGNAL(registered()));
    connect(m_defaultClient, SIGNAL(registerTimeout()), this, SIGNAL(registerTimeout()));
    connect(m_defaultClient, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    connect(m_defaultClient, SIGNAL(nameChanged(QString)), this, SIGNAL(nameChanged(QString)));
    connect(m_defaultClient, SIGNAL(sexChanged(QString)), this, SIGNAL(sexChanged(QString)));
    connect(m_defaultClient, SIGNAL(ageChanged(QString)), this, SIGNAL(ageChanged(QString)));
    connect(m_defaultClient, SIGNAL(bedChanged(QString)), this, SIGNAL(bedChanged(QString)));
    connect(m_defaultClient, SIGNAL(levelChanged(QString)), this, SIGNAL(levelChanged(QString)));
    connect(m_defaultClient, SIGNAL(timeChanged(QString)), this, SIGNAL(timeChanged(QString)));
    connect(m_defaultClient, SIGNAL(doctorChanged(QString)), this, SIGNAL(doctorChanged(QString)));
    connect(m_defaultClient, SIGNAL(eatChanged(QString)), this, SIGNAL(eatChanged(QString)));
    connect(m_defaultClient, SIGNAL(nurseChanged(QString)), this, SIGNAL(nurseChanged(QString)));
    connect(m_defaultClient, SIGNAL(adviseChanged(QString)), this, SIGNAL(adviseChanged(QString)));
    connect(m_defaultClient, SIGNAL(allergyChanged(QString)), this, SIGNAL(allergyChanged(QString)));
    connect(m_defaultClient, SIGNAL(adviseUpdate(QString)), this, SIGNAL(adviseUpdate(QString)));
    connect(m_defaultClient, SIGNAL(motorMove(QMap<quint8,quint8>)),
            this, SIGNAL(motorMove(QMap<quint8,quint8>)));

    return true;
}

void NetworkModule::unload()
{
    delete m_defaultClient;
}

void NetworkModule::init()
{
    m_defaultClient->connectServer(ServerManger::instance().address(ServerManger::Default),
                                   ServerManger::instance().port(ServerManger::Default));
}

void NetworkModule::reconnect(const QString &ip, quint16 port, quint16 device)
{
    m_defaultClient->setDeviceNum(device);
    m_defaultClient->connectServer(ip, port);
}

void NetworkModule::getAdvise()
{
    m_defaultClient->getAdvise();
}

void NetworkModule::uploadInOut(const QStringList &data)
{
    m_defaultClient->uploadInOut(data);
}

void NetworkModule::sendInfuStatus(int status)
{
    m_defaultClient->sendInfuStatus(status);
}

void NetworkModule::sendInfuSpeed(int speed)
{
    m_defaultClient->sendInfuSpeed(speed);
}

void NetworkModule::sendInfuLeft(int left)
{
    m_defaultClient->sendInfuLeft(left);
}

void NetworkModule::sendWeight(double weight)
{
    m_defaultClient->sendWeight(static_cast<char>(weight));
}
