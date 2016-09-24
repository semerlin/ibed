#include <QMutex>
#include <QByteArray>
#include "idatahandler.h"
#include "beddataprocess.h"
#include "boost/foreach.hpp"
#include "crc.h"
#include "infucountdatahandler.h"
#include "infuspeeddatahandler.h"
#include "infumountdatahandler.h"
#include "weightdatahandler.h"
#include "applogger.h"
#include "modbus.h"
#include <QDebug>

BedDataProcess::BedDataProcess(quint8 address) :
    m_mutex(new QMutex),
    m_contentLen(0),
    m_address(address)
{
    InfuCountDataHandler *countHandler = new InfuCountDataHandler(0x04, 69);
    InfuSpeedDataHandler *speedHandler = new InfuSpeedDataHandler(0x04, 70);
    InfuMountDataHandler *mountHandler = new InfuMountDataHandler(0x04, 71);
    WeightDataHandler *weightHandler = new WeightDataHandler(0x04, 80);

    addDataHandler(countHandler);
    addDataHandler(speedHandler);
    addDataHandler(mountHandler);
    addDataHandler(weightHandler);

    connect(countHandler, SIGNAL(countChanged(int)), this, SIGNAL(infuCountChanged(int)), Qt::QueuedConnection);
    connect(speedHandler, SIGNAL(speedChanged(int)), this, SIGNAL(infuSpeedChanged(int)), Qt::QueuedConnection);
    connect(mountHandler, SIGNAL(mountChanged(int)), this, SIGNAL(infuMountChanged(int)), Qt::QueuedConnection);
    connect(weightHandler, SIGNAL(weightChanged(double)), this, SIGNAL(weightChanged(double)), Qt::QueuedConnection);
}

void BedDataProcess::setContentLen(quint8 len)
{
    m_mutex->lock();
    m_contentLen = len;
    m_mutex->unlock();
}

void BedDataProcess::setRegAddress(quint16 address)
{
    m_mutex->lock();
    m_regAddress = address;
    m_mutex->unlock();
}

void BedDataProcess::onProcessData(const QByteArray &data)
{
//    printRecvData(data);

    //start processing
    m_mutex->lock();
    m_data.append(data);
    quint8 contentlen = m_contentLen;
    quint16 regAddress = m_regAddress;

    if(m_data.count() >= (contentlen + 4))
    {
        //seek to head
        int index = m_data.indexOf(m_address);
        m_data.remove(0, index);

        //check length again
        if(m_data.count() >= (contentlen + 4))
        {
            //get valid data
            QByteArray validData;
            for(int i = 0; i < contentlen + 4; ++i)
                validData.append(m_data.at(i));
            m_data.remove(0, contentlen + 4);
            m_mutex->unlock();

            //check CRC
            quint16 crc = CRC::mbCRC16((quint8 *)validData.data(), contentlen + 2);
            quint16 rCrc = (validData.at(contentlen + 3) & 0xff);
            rCrc <<= 8;
            rCrc += (validData.at(contentlen + 2) & 0xff);
            if(crc == rCrc)
            {
                //find handler
                quint8 fucCode = (validData.at(1) & 0xff);

                BOOST_FOREACH(IDataHandler *handler, m_handlers)
                {
                    if((handler->fucCode() == fucCode) && (handler->regAddress() == regAddress))
                    {
                        handler->handle(fucCode, regAddress, validData);
                        break;
                    }
                }
            }
        }
        else
            m_mutex->unlock();
    }
    else
        m_mutex->unlock();
}

void BedDataProcess::reset()
{
    m_mutex->lock();
    m_data.clear();
    m_mutex->unlock();
}

void BedDataProcess::addDataHandler(IDataHandler *handler)
{
    m_mutex->lock();

    if(handler != NULL)
        m_handlers.append(handler);

    m_mutex->unlock();
}

void BedDataProcess::printRecvData(const QByteArray &data)
{
    //print modbus data
    QString printData;
    for(int i = 0; i < data.count(); ++i)
    {
        printData += QString::number((quint8)data.at(i), 16);
        printData += " ";
    }
    AppLogger::instance().log()->debug("Modbus: " + printData);
}

