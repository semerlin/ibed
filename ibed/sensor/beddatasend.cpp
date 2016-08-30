#include "bedcontrol.h"
#include <QMutex>
#include <QWaitCondition>
#include "beddatasend.h"
#include "modbus.h"
#include "unistd.h"

BedDataSend::BedDataSend(BedControl *parent) :
    m_control(parent),
    m_waitMutex(new QMutex),
    m_waitCondition(new QWaitCondition)
{
    start();
}

BedDataSend::~BedDataSend()
{
    quit();
}

void BedDataSend::appendSendData(const BedDataSend::ModbusData &data)
{
    m_dataQueue.enqueue(data);
    m_waitCondition->wakeAll();
}

void BedDataSend::run()
{
    while(1)
    {
        m_waitMutex->lock();
        m_waitCondition->wait(m_waitMutex);

        while(m_dataQueue.count() > 0)
        {
            ModbusData data = m_dataQueue.dequeue();
            m_control->m_modbus->write(data.m_code, data.m_address, data.m_data.data(), data.m_data.count());
            //sleep 100ms
            ::usleep(100000);
        }

        m_waitMutex->unlock();
    }
}

