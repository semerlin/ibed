#include "bedcontrol.h"
#include <QMutex>
#include <QWaitCondition>
#include "beddatasend.h"
#include "modbus.h"
#include "unistd.h"
#include "powercontrol.h"

BedDataSend::BedDataSend(BedControl *parent) :
    m_control(parent),
    m_waitMutex(new QMutex),
    m_mutex(new QMutex),
    m_waitCondition(new QWaitCondition)
{
    start();
}

BedDataSend::~BedDataSend()
{
    quit();
}

void BedDataSend::appendSendData(BedDataSend::ModbusData *data)
{
    if(data == NULL)
        return;

    m_mutex->lock();
    m_dataQueue.enqueue(data);
    m_mutex->unlock();
    m_waitCondition->wakeAll();
}

void BedDataSend::run()
{
    while(1)
    {
        m_waitMutex->lock();
//        if(m_dataQueue.count() <= 0)
            m_waitCondition->wait(m_waitMutex);

        while(m_dataQueue.count() > 0)
        {
            m_mutex->lock();
            ModbusData *data = m_dataQueue.dequeue();
            m_mutex->unlock();

#ifdef TARGET_IMX
            PowerControl::instance().rs485DirectCtrl(1);
#endif
            m_control->m_modbus->write(data->m_code, data->m_address, data->m_data.data(), data->m_data.count());

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
            delete data;
            //sleep 100ms
            ::usleep(100000);
        }

        m_waitMutex->unlock();
    }
}

