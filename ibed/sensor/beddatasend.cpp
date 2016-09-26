#include "bedcontrol.h"
#include <QMutex>
#include <QWaitCondition>
#include "beddatasend.h"
#include "modbus.h"
#include "unistd.h"
#include "powercontrol.h"
#include "beddataprocess.h"

BedDataSend::BedDataSend(BedControl *parent) :
    m_control(parent),
    m_mutex(new QMutex)
{
    start();
}

BedDataSend::~BedDataSend()
{
    quit();
}

void BedDataSend::appendSendData(const ModbusData &data)
{
    m_mutex->lock();
    m_dataQueue.enqueue(data);
    m_mutex->unlock();
}

void BedDataSend::run()
{
    while(1)
    {
        while(m_dataQueue.count() > 0)
        {
            m_mutex->lock();
            ModbusData data = m_dataQueue.dequeue();
            m_mutex->unlock();

#ifdef TARGET_IMX
            PowerControl::instance().rs485DirectCtrl(1);
#endif
            m_control->m_process->reset();
            switch(data.m_code)
            {
            case Modbus::WRITE_SingleRegister:
                m_control->m_process->setRegAddress(data.m_address);
                m_control->m_process->setContentLen(4);
                m_control->m_modbus->write(data.m_code, data.m_address, data.m_data.data(), data.m_data.count());
                break;
            case Modbus::READ_InputRegister:
                m_control->m_process->setRegAddress(data.m_address);
                m_control->m_process->setContentLen(3);
                m_control->m_modbus->write(data.m_code, data.m_address, data.m_data.data(), data.m_data.count());
                break;
            default:
                break;
            }


#ifdef TARGET_IMX
            PowerControl::instance().rs485DirectCtrl(0);
#endif
            //sleep 100ms
            ::usleep(100000);
        }

        ::usleep(500000);
    }
}


