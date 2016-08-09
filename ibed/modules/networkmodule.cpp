#include "defaultclient.h"
#include "registerdatahandler.h"
#include "networkmodule.h"
#include "servermanger.h"

NetworkModule::NetworkModule(const QString &name) :
    BaseAppModule(name),
    m_defaultClient(new DefaultClient)
{

}

NetworkModule::~NetworkModule()
{
    unload();
}

bool NetworkModule::load(const QVariant &val)
{
    Q_UNUSED(val)

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

void NetworkModule::reconnect(const QString &ip, quint16 port)
{
    m_defaultClient->connectServer(ip, port);
}
