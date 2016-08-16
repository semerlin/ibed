#include <QMutex>
#include "idatahandler.h"
#include "netprotocol.h"
#include <QTcpSocket>
#include "defaultclient.h"
#include "registerdatahandler.h"
#include "heartbeatdatahandler.h"
#include "baseinfodatahandler.h"
#include "advisedatahandler.h"
#include "servermanger.h"
#include <QTimer>
#include <QHostAddress>
#include <QStringList>

#define HEARTCNT_MAX (3)

DefaultClient::DefaultClient() :
    m_socket(new QTcpSocket),
    m_mutex(new QMutex()),
    m_protocol(new NetProtocol),
    m_isRegistered(false),
    m_heartTimer(new QTimer(this)),
    m_heartCnt(0)
{
    connect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadReady()));

    RegisterDataHandler *regHandle = new RegisterDataHandler(2);
    connect(regHandle, SIGNAL(registered()), this, SLOT(onRegistered()));
    addHandler(regHandle);

    //heartreat handler
    HeartBeatDataHandler *heartHandle = new HeartBeatDataHandler(1);
    connect(heartHandle, SIGNAL(heartbeat()), this, SLOT(onHeartOk()));
    addHandler(heartHandle);

    //baseinfo handler
    BaseinfoDataHandler *baseHandle = new BaseinfoDataHandler(80);
    connect(baseHandle, SIGNAL(nameChanged(QString)), this, SIGNAL(nameChanged(QString)));
    connect(baseHandle, SIGNAL(sexChanged(QString)), this, SIGNAL(sexChanged(QString)));
    connect(baseHandle, SIGNAL(ageChanged(QString)), this, SIGNAL(ageChanged(QString)));
    connect(baseHandle, SIGNAL(bedChanged(QString)), this, SIGNAL(bedChanged(QString)));
    connect(baseHandle, SIGNAL(levelChanged(QString)), this, SIGNAL(levelChanged(QString)));
    connect(baseHandle, SIGNAL(timeChanged(QString)), this, SIGNAL(timeChanged(QString)));
    connect(baseHandle, SIGNAL(doctorChanged(QString)), this, SIGNAL(doctorChanged(QString)));
    connect(baseHandle, SIGNAL(eatChanged(QString)), this, SIGNAL(eatChanged(QString)));
    connect(baseHandle, SIGNAL(nurseChanged(QString)), this, SIGNAL(nurseChanged(QString)));
    connect(baseHandle, SIGNAL(adviseChanged(QString)), this, SIGNAL(adviseChanged(QString)));
    connect(baseHandle, SIGNAL(allergyChanged(QString)), this, SIGNAL(allergyChanged(QString)));
    addHandler(baseHandle);

    //adviseinfo handler
    AdviseDataHandler *adviseHandler = new AdviseDataHandler(101);
    connect(adviseHandler, SIGNAL(adviseUpdate(QString)), this, SIGNAL(adviseUpdate(QString)));
    addHandler(adviseHandler);

    //heartbeat timer
    m_heartTimer->setInterval(1000);
    connect(m_heartTimer, SIGNAL(timeout()), this, SLOT(onHeartbeat()));
    m_heartTimer->start();

}

DefaultClient::~DefaultClient()
{
    if(m_socket->state() == QAbstractSocket::ConnectedState)
    {
        //socket already connect to server, so disconnect
        m_socket->disconnectFromHost();
        m_socket->waitForDisconnected(1000);
    }
    delete m_socket;
    delete m_mutex;
    delete m_protocol;
    qDeleteAll(m_handlers);
}

void DefaultClient::connectServer(const QString &ip, quint16 port)
{
    clear();
    m_socket->connectToHost(QHostAddress(ip), port);

    QTimer::singleShot(3000, this, SLOT(onConnectTimeout()));
}

void DefaultClient::addHandler(IDataHandler *handler)
{
    if(!m_handlers.contains(handler->msgId()))
    {
        m_handlers[handler->msgId()] = handler;
    }
}

bool DefaultClient::isRegistered() const
{
    return m_isRegistered;
}

void DefaultClient::getAdvise()
{
    m_socket->write(m_protocol->package(NetProtocol::AdviseInfo));
}

void DefaultClient::getBaseInfo()
{
    m_socket->write(m_protocol->package(NetProtocol::BaseInfo));
}

void DefaultClient::uploadInOut(const QStringList &data)
{
    NetProtocol::ContentList list;
    NetProtocol::Content content;

    content.id = 10220;
    content.length = data.at(0).size();
    content.data = data.at(0).toLatin1();
    list.append(content);

    content.id = 10221;
    content.length = data.at(1).size();
    content.data = data.at(1).toLatin1();
    list.append(content);

    content.id = 10222;
    content.length = data.at(2).size();
    content.data = data.at(2).toLatin1();
    list.append(content);

    content.id = 10226;
    content.length = data.at(3).size();
    content.data = data.at(3).toLatin1();
    list.append(content);

    content.id = 10224;
    content.length = data.at(4).size();
    content.data = data.at(4).toLatin1();
    list.append(content);

    content.id = 10227;
    content.length = data.at(5).size();
    content.data = data.at(5).toLatin1();
    list.append(content);

    content.id = 10228;
    content.length = data.at(6).size();
    content.data = data.at(6).toLatin1();
    list.append(content);

    content.id = 10223;
    content.length = data.at(7).size();
    content.data = data.at(7).toLatin1();
    list.append(content);

    content.id = 10225;
    content.length = data.at(8).size();
    content.data = data.at(8).toLatin1();
    list.append(content);

    content.id = 10250;
    content.length = data.at(9).size();
    content.data = data.at(9).toLatin1();
    list.append(content);

    content.id = 10251;
    content.length = data.at(10).size();
    content.data = data.at(10).toLatin1();
    list.append(content);

    content.id = 10252;
    content.length = data.at(11).size();
    content.data = data.at(11).toLatin1();
    list.append(content);

    m_socket->write(m_protocol->package(NetProtocol::InOutInfo, list));
}

void DefaultClient::onConnectTimeout()
{
    if(m_socket->state() != QAbstractSocket::ConnectedState)
    {
        emit connectTimeout();
        emit registerTimeout();
    }
}

void DefaultClient::onConnected()
{
    //start register
    m_socket->write(m_protocol->package(NetProtocol::Register));
    QTimer::singleShot(3000, this, SLOT(onRegisterTimeout()));
}

void DefaultClient::onDisconnected()
{
    m_data.clear();
    m_mutex->unlock();
    m_isRegistered = false;
    emit disconnected();
}

void DefaultClient::onReadReady()
{
    QByteArray data;
    //append data
    do
    {
        //perhaps there is more than one invalid packages in one buffer
        m_mutex->lock();
        m_data.append(m_socket->read(m_socket->bytesAvailable()));
        data = m_protocol->tryUnpackage(m_data);
        m_mutex->unlock();

        if(data.count() > 0)
        {
            NetProtocol::ContentList list;
            quint8 id;
            list = m_protocol->unpackage(data, id);
            if(m_handlers.contains(id))
                m_handlers[id]->handle(id, list);

            emit dataReached(id, list);
        }
    }while(data.count() > 0);
}

void DefaultClient::onRegisterTimeout()
{
    if(!m_isRegistered)
        emit registerTimeout();
}

void DefaultClient::onRegistered()
{
    m_isRegistered = true;
    m_socket->write(m_protocol->package(NetProtocol::BaseInfo));
    emit registered();
}

void DefaultClient::onHeartbeat()
{
    if(m_isRegistered)
    {
        //heartbeat
        m_socket->write(m_protocol->package(NetProtocol::HeartBeat));

        if(++m_heartCnt > HEARTCNT_MAX)
            clear();
    }
}

void DefaultClient::onHeartOk()
{
    m_heartCnt = 0;
}

void DefaultClient::clear()
{
    m_isRegistered = false;
    m_socket->disconnectFromHost();
    m_data.clear();
    m_mutex->unlock();
    m_heartCnt = 0;
}
