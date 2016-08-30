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

BedDataProcess::BedDataProcess(quint8 address) :
    m_mutex(new QMutex),
    m_contentLen(0),
    m_address(address)
{
    InfuCountDataHandler *countHandler = new InfuCountDataHandler(0x04, 0x69);
    InfuSpeedDataHandler *speedHandler = new InfuSpeedDataHandler(0x04, 0x70);
    InfuMountDataHandler *mountHandler = new InfuMountDataHandler(0x04, 0x71);
    WeightDataHandler *weightHandler = new WeightDataHandler(0x04, 0x79);

    addDataHandler(countHandler);
    addDataHandler(speedHandler);
    addDataHandler(mountHandler);
    addDataHandler(weightHandler);

    connect(countHandler, SIGNAL(countChanged(int)), this, SIGNAL(infuCountChanged(int)));
    connect(speedHandler, SIGNAL(speedChanged(int)), this, SIGNAL(infuSpeedChanged(int)));
    connect(mountHandler, SIGNAL(mountChanged(int)), this, SIGNAL(infuMountChanged(int)));
    connect(weightHandler, SIGNAL(weightChanged(double)), this, SIGNAL(weightChanged(double)));
}

void BedDataProcess::setContentLen(quint8 len)
{
    m_mutex->lock();
    m_contentLen = len;
    m_mutex->unlock();
}

void BedDataProcess::onProcessData(const QByteArray &data)
{
    //print modbus data
    QString printData;
    for(int i = 0; i < data.count(); ++i)
    {
        printData += QString::number(data.at(i), 16);
        printData += " ";
    }
    AppLogger::instance().log()->debug("Modbus: " + printData);

    //start processing
    m_mutex->lock();
    m_data.append(data);

    if(m_data.count() >= (m_contentLen + 6))
    {
        //seek to head
        int index = m_data.indexOf(m_address);
        m_data.remove(0, index);

        //check length again
        if(m_data.count() >= (m_contentLen + 6))
        {
            //get valid data
            QByteArray validData;
            for(int i = 0; i < m_contentLen + 6; ++i)
                validData.append(m_data.at(i));
            m_data.remove(0, m_contentLen + 6);
            m_mutex->unlock();

            //check CRC
            quint16 crc = CRC::mbCRC16((quint8 *)validData.data(), m_contentLen + 4);
            quint16 rCrc = validData.at(m_contentLen + 5);
            rCrc <<= 8;
            rCrc += validData.at(m_contentLen + 4) ;
            if(crc == rCrc)
            {
                //find handler
                quint8 fucCode = validData.at(1);
                quint16 regAddress = validData.at(2);
                regAddress <<= 8;
                regAddress += validData.at(3);
                BOOST_FOREACH(IDataHandler *handler, m_handlers)
                {
                    if((handler->fucCode() == fucCode) && (handler->regAddress() == regAddress))
                    {
                        handler->handle(fucCode, regAddress, validData);
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

void BedDataProcess::addDataHandler(IDataHandler *handler)
{
    m_mutex->lock();

    if(handler != NULL)
        m_handlers.append(handler);

    m_mutex->unlock();
}

