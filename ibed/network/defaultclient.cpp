#include <QMutex>
#include <QThread>
#include "defaultdataprocess.h"
#include "idatahandler.h"
#include "netprotocol.h"
#include <QTcpSocket>
#include "defaultclient.h"
#include "servermanger.h"
#include <QTimer>
#include <QHostAddress>
#include <QStringList>

#define HEARTCNT_MAX (3)

DefaultClient::DefaultClient() :
    m_socket(new QTcpSocket),
    m_isRegistered(false),
    m_heartTimer(new QTimer(this)),
    m_heartCnt(0),
    m_dataProcess(new DefaultDataProcess),
    m_dataThread(new QThread)
{
    connect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadReady()));

    connect(this, SIGNAL(dataReached(QByteArray)), m_dataProcess, SLOT(onProcessData(QByteArray)),
            Qt::QueuedConnection);

    //move data process to thread
    m_dataProcess->moveToThread(m_dataThread);
    m_dataThread->start();

    //register and heartbeat
    connect(m_dataProcess, SIGNAL(registered()), this, SLOT(onRegistered()));
    connect(m_dataProcess, SIGNAL(heartbeat()), this, SLOT(onHeartOk()));

    //base info
    connect(m_dataProcess, SIGNAL(nameChanged(QString)), this, SIGNAL(nameChanged(QString)));
    connect(m_dataProcess, SIGNAL(sexChanged(QString)), this, SIGNAL(sexChanged(QString)));
    connect(m_dataProcess, SIGNAL(ageChanged(QString)), this, SIGNAL(ageChanged(QString)));
    connect(m_dataProcess, SIGNAL(bedChanged(QString)), this, SIGNAL(bedChanged(QString)));
    connect(m_dataProcess, SIGNAL(levelChanged(QString)), this, SIGNAL(levelChanged(QString)));
    connect(m_dataProcess, SIGNAL(timeChanged(QString)), this, SIGNAL(timeChanged(QString)));
    connect(m_dataProcess, SIGNAL(doctorChanged(QString)), this, SIGNAL(doctorChanged(QString)));
    connect(m_dataProcess, SIGNAL(eatChanged(QString)), this, SIGNAL(eatChanged(QString)));
    connect(m_dataProcess, SIGNAL(nurseChanged(QString)), this, SIGNAL(nurseChanged(QString)));
    connect(m_dataProcess, SIGNAL(adviseChanged(QString)), this, SIGNAL(adviseChanged(QString)));
    connect(m_dataProcess, SIGNAL(allergyChanged(QString)), this, SIGNAL(allergyChanged(QString)));

    //advise info
    connect(m_dataProcess, SIGNAL(adviseUpdate(QString)), this, SIGNAL(adviseUpdate(QString)));

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
    delete m_dataThread;
    delete m_dataProcess;
}

void DefaultClient::connectServer(const QString &ip, quint16 port)
{
    clear();
    m_socket->connectToHost(QHostAddress(ip), port);

    QTimer::singleShot(3000, this, SLOT(onConnectTimeout()));
}



bool DefaultClient::isRegistered() const
{
    return m_isRegistered;
}

void DefaultClient::getAdvise()
{
    m_socket->write(m_dataProcess->package(NetProtocol::AdviseInfo));
}

void DefaultClient::getBaseInfo()
{
    m_socket->write(m_dataProcess->package(NetProtocol::BaseInfo));
}

void DefaultClient::uploadInOut(const QStringList &data)
{
    if(m_isRegistered)
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

        m_socket->write(m_dataProcess->package(NetProtocol::InOutInfo, list));
    }
}

void DefaultClient::sendInfuStatus(int status)
{
    if(m_isRegistered)
    {
        NetProtocol::ContentList list;
        NetProtocol::Content content;

        content.id = 3310;
        content.length = 1;
        content.data.append(static_cast<char>(status));
        list.append(content);


        m_socket->write(m_dataProcess->package(NetProtocol::InfuInfo, list));
    }
}

void DefaultClient::sendInfuSpeed(int speed)
{
    if(m_isRegistered)
    {
        NetProtocol::ContentList list;
        NetProtocol::Content content;

        content.id = 3311;
        content.length = 1;
        content.data.append(static_cast<char>(speed));
        list.append(content);


        m_socket->write(m_dataProcess->package(NetProtocol::InfuInfo, list));
    }
}

void DefaultClient::sendInfuLeft(int left)
{
    if(m_isRegistered)
    {
        NetProtocol::ContentList list;
        NetProtocol::Content content;

        content.id = 3312;
        content.length = 1;
        content.data.append(static_cast<char>(left));
        list.append(content);


        m_socket->write(m_dataProcess->package(NetProtocol::InfuInfo, list));
    }
}

void DefaultClient::sendWeight(int weight)
{
    if(m_isRegistered)
    {
        NetProtocol::ContentList list;
        NetProtocol::Content content;

        content.id = 3431;
        content.length = 1;
        content.data.append(static_cast<char>(weight));
        list.append(content);


        m_socket->write(m_dataProcess->package(NetProtocol::Spo2Info, list));
    }
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
    m_socket->write(m_dataProcess->package(NetProtocol::Register));
    QTimer::singleShot(3000, this, SLOT(onRegisterTimeout()));
}

void DefaultClient::onDisconnected()
{
    m_dataProcess->reset();
    m_isRegistered = false;
    emit disconnected();
}

void DefaultClient::onReadReady()
{
    emit dataReached(m_socket->read(m_socket->bytesAvailable()));
}

void DefaultClient::onRegisterTimeout()
{
    if(!m_isRegistered)
        emit registerTimeout();
}

void DefaultClient::onRegistered()
{
    m_isRegistered = true;
    m_socket->write(m_dataProcess->package(NetProtocol::BaseInfo));
    emit registered();
}

void DefaultClient::onHeartbeat()
{
    if(m_isRegistered)
    {
        //heartbeat
        m_socket->write(m_dataProcess->package(NetProtocol::HeartBeat));

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
    m_dataProcess->reset();
    m_heartCnt = 0;
}

