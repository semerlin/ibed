#include <QMutex>
#include <QThread>
#include "defaultdataprocess.h"
#include "idatahandler.h"
#include "netprotocol.h"
#include <QTcpSocket>
#include "defaultclient.h"
#include "servermanager.h"
#include <QTimer>
#include <QHostAddress>
#include <QStringList>
#include "netconfig.h"
#include "systemcall.h"
#include "unistd.h"
#include "applogger.h"
#include "log4qt/logger.h"

#define HEARTCNT_MAX (3)

DefaultClient::DefaultClient() :
    m_socket(new QTcpSocket),
    m_isRegistered(false),
    m_heartTimer(new QTimer(this)),
    m_heartCnt(0),
    m_dataProcess(new DefaultDataProcess),
    m_dataThread(new QThread),
    m_ip(NetConfig::instance().address()),
    m_netmask(NetConfig::instance().netmask()),
    m_gateway(NetConfig::instance().gateway())
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
    connect(m_dataProcess, SIGNAL(registered()), this, SLOT(onRegistered()), Qt::QueuedConnection);
    connect(m_dataProcess, SIGNAL(heartbeat()), this, SLOT(onHeartOk()), Qt::QueuedConnection);

    //base info
    connect(m_dataProcess, SIGNAL(nameChanged(QString)), this, SIGNAL(nameChanged(QString)), Qt::QueuedConnection);
    connect(m_dataProcess, SIGNAL(sexChanged(QString)), this, SIGNAL(sexChanged(QString)), Qt::QueuedConnection);
    connect(m_dataProcess, SIGNAL(ageChanged(QString)), this, SIGNAL(ageChanged(QString)), Qt::QueuedConnection);
    connect(m_dataProcess, SIGNAL(bedChanged(QString)), this, SIGNAL(bedChanged(QString)), Qt::QueuedConnection);
    connect(m_dataProcess, SIGNAL(levelChanged(QString)), this, SIGNAL(levelChanged(QString)), Qt::QueuedConnection);
    connect(m_dataProcess, SIGNAL(timeChanged(QString)), this, SIGNAL(timeChanged(QString)), Qt::QueuedConnection);
    connect(m_dataProcess, SIGNAL(doctorChanged(QString)), this, SIGNAL(doctorChanged(QString)), Qt::QueuedConnection);
    connect(m_dataProcess, SIGNAL(eatChanged(QString)), this, SIGNAL(eatChanged(QString)), Qt::QueuedConnection);
    connect(m_dataProcess, SIGNAL(nurseChanged(QString)), this, SIGNAL(nurseChanged(QString)), Qt::QueuedConnection);
    connect(m_dataProcess, SIGNAL(adviseChanged(QString)), this, SIGNAL(adviseChanged(QString)), Qt::QueuedConnection);
    connect(m_dataProcess, SIGNAL(allergyChanged(QString)), this, SIGNAL(allergyChanged(QString)), Qt::QueuedConnection);

    //advise info
    connect(m_dataProcess, SIGNAL(adviseUpdate(QString)), this, SIGNAL(adviseUpdate(QString)), Qt::QueuedConnection);

    //bed control
    connect(m_dataProcess, SIGNAL(motorMove(QMap<quint8,quint8>)),
            this, SIGNAL(motorMove(QMap<quint8,quint8>)));

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

    QTimer::singleShot(5000, this, SLOT(onConnectTimeout()));
}



bool DefaultClient::isRegistered() const
{
    return m_isRegistered;
}

void DefaultClient::getAdvise()
{
    socketWrite(m_dataProcess->package(NetProtocol::AdviseInfo));
}

void DefaultClient::getBaseInfo()
{
    socketWrite(m_dataProcess->package(NetProtocol::BaseInfo));
    socketWrite(m_dataProcess->package(NetProtocol::DocAdvise));
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

        socketWrite(m_dataProcess->package(NetProtocol::InOutInfo, list));
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


        socketWrite(m_dataProcess->package(NetProtocol::InfuInfo, list));
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


        socketWrite(m_dataProcess->package(NetProtocol::InfuInfo, list));
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


        socketWrite(m_dataProcess->package(NetProtocol::InfuInfo, list));
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


        socketWrite(m_dataProcess->package(NetProtocol::Spo2Info, list));
    }
}

void DefaultClient::setDeviceNum(quint16 device)
{
    m_dataProcess->setDeviceNum(device);
}

void DefaultClient::setLocalInfo(const QString &ip, const QString &netmask, const QString &gateway)
{
#ifdef TARGET_IMX
    bool needCfg = false;
    if(m_ip != ip)
        needCfg = true;
    if(m_netmask != netmask)
        needCfg = true;
    if(m_gateway != gateway)
        needCfg = true;

    if(needCfg)
    {
//        AppLogger::instance().log()->debug("reconfigure network");
        clear();
        //reconnect signals
        disconnect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
        disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadReady()));

        delete m_socket;
        //set local address
        SystemCall::system(QString("./ethcfg %1 %2 %3 %4")
                        .arg(NetConfig::instance().name())
                        .arg(ip)
                        .arg(netmask)
                        .arg(gateway));

        QTimer::singleShot(2000, this, SLOT(onReconnect()));
    }
#endif
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
    QTimer::singleShot(5000, this, SLOT(onRegisterTimeout()));
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
    socketWrite(m_dataProcess->package(NetProtocol::BaseInfo));
    socketWrite(m_dataProcess->package(NetProtocol::DocAdvise));
    emit registered();
}

void DefaultClient::onHeartbeat()
{
    if(m_isRegistered)
    {
        //heartbeat
        socketWrite(m_dataProcess->package(NetProtocol::HeartBeat));

        if(++m_heartCnt > HEARTCNT_MAX)
            clear();
    }
}

void DefaultClient::onHeartOk()
{
    m_heartCnt = 0;
}

void DefaultClient::onReconnect()
{
    m_socket = new QTcpSocket;
    connect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadReady()));

}

void DefaultClient::clear()
{
    m_isRegistered = false;
    m_socket->flush();
    m_socket->disconnectFromHost();
    m_dataProcess->reset();
    m_heartCnt = 0;
}

bool DefaultClient::socketWrite(const QByteArray &data)
{
    bool flag = false;
    if(m_isRegistered)
    {
        m_socket->write(data);
        flag = m_socket->waitForBytesWritten(10);
    }
    return flag;
}


