#include <QMutex>
#include "netprotocol.h"
#include "idatahandler.h"
#include "defaultdataprocess.h"
#include "registerdatahandler.h"
#include "heartbeatdatahandler.h"
#include "baseinfodatahandler.h"
#include "advisedatahandler.h"
#include "docadvisedatahandler.h"
#include "bedcontroldatahandler.h"
#include "qmetatype.h"
#include <QDebug>

DefaultDataProcess::DefaultDataProcess() :
    m_mutex(new QMutex),
    m_protocol(new NetProtocol)
{
    qRegisterMetaType<QMap<quint8, quint8> >("QMap<quint8, quint8>");
    RegisterDataHandler *regHandle = new RegisterDataHandler(2);
    connect(regHandle, SIGNAL(registered()), this, SIGNAL(registered()));
    addHandler(regHandle);

    //heartreat handler
    HeartBeatDataHandler *heartHandle = new HeartBeatDataHandler(1);
    connect(heartHandle, SIGNAL(heartbeat()), this, SIGNAL(heartbeat()));
    addHandler(heartHandle);

    //baseinfo handler
    BaseinfoDataHandler *baseHandle = new BaseinfoDataHandler(80);
    connect(baseHandle, SIGNAL(nameChanged(QString)), this, SIGNAL(nameChanged(QString)), Qt::QueuedConnection);
    connect(baseHandle, SIGNAL(sexChanged(QString)), this, SIGNAL(sexChanged(QString)), Qt::QueuedConnection);
    connect(baseHandle, SIGNAL(ageChanged(QString)), this, SIGNAL(ageChanged(QString)), Qt::QueuedConnection);
    connect(baseHandle, SIGNAL(bedChanged(QString)), this, SIGNAL(bedChanged(QString)), Qt::QueuedConnection);
    connect(baseHandle, SIGNAL(levelChanged(QString)), this, SIGNAL(levelChanged(QString)), Qt::QueuedConnection);
    connect(baseHandle, SIGNAL(timeChanged(QString)), this, SIGNAL(timeChanged(QString)), Qt::QueuedConnection);
    connect(baseHandle, SIGNAL(doctorChanged(QString)), this, SIGNAL(doctorChanged(QString)), Qt::QueuedConnection);
    connect(baseHandle, SIGNAL(eatChanged(QString)), this, SIGNAL(eatChanged(QString)), Qt::QueuedConnection);
    connect(baseHandle, SIGNAL(nurseChanged(QString)), this, SIGNAL(nurseChanged(QString)), Qt::QueuedConnection);
    connect(baseHandle, SIGNAL(allergyChanged(QString)), this, SIGNAL(allergyChanged(QString)), Qt::QueuedConnection);
    addHandler(baseHandle);

    //doctor advise handler
    DocAdviseDataHandler *docAdviseHandler = new DocAdviseDataHandler(81);
    connect(docAdviseHandler, SIGNAL(adviseChanged(QString)), this, SIGNAL(adviseChanged(QString)), Qt::QueuedConnection);
    addHandler(docAdviseHandler);

    //adviseinfo handler
    AdviseDataHandler *adviseHandler = new AdviseDataHandler(101);
    connect(adviseHandler, SIGNAL(adviseUpdate(QString)), this, SIGNAL(adviseUpdate(QString)), Qt::QueuedConnection);
    addHandler(adviseHandler);

    //bed control data handler
    BedControlDataHandler *bedHandler = new BedControlDataHandler(15);
    connect(bedHandler, SIGNAL(motorMove(QMap<quint8,quint8>)),
            this, SIGNAL(motorMove(QMap<quint8,quint8>)), Qt::QueuedConnection);
    addHandler(bedHandler);
}

DefaultDataProcess::~DefaultDataProcess()
{
    delete m_mutex;
    delete m_protocol;
    qDeleteAll(m_handlers);
}

void DefaultDataProcess::onProcessData(const QByteArray &newData)
{
    QByteArray data;
    //print network data
//    QString printData;
//    for(int i = 0; i < newData.count(); ++i)
//    {
//        printData += QString::number((quint8)newData.at(i), 16);
//        printData += " ";
//    }
//    qDebug() << "network: " << printData;
    //append data
    m_mutex->lock();
    m_data.append(newData);
    m_mutex->unlock();

    do
    {
        //perhaps there is more than one valid packages in one buffer
        m_mutex->lock();
        data = m_protocol->tryUnpackage(m_data);
        m_mutex->unlock();

        if(data.count() > 0)
        {
            NetProtocol::ContentList list;
            quint8 id;
            list = m_protocol->unpackage(data, id);
            if(m_handlers.contains(id))
                m_handlers[id]->handle(id, list);
        }
    }while(data.count() > 0);
}

void DefaultDataProcess::addHandler(IDataHandler *handler)
{
    m_mutex->lock();
    if(!m_handlers.contains(handler->msgId()))
    {
        m_handlers[handler->msgId()] = handler;
    }
    m_mutex->unlock();
}

void DefaultDataProcess::reset()
{
    m_mutex->lock();
    m_data.clear();
    m_mutex->unlock();
}

QByteArray DefaultDataProcess::package(quint8 id, const NetProtocol::ContentList &contents)
{
    return m_protocol->package(id, contents);
}

void DefaultDataProcess::setDeviceNum(quint16 device)
{
    m_protocol->setDeviceNum(device);
}

