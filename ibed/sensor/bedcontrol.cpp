#include <QMutex>
#include <QThread>
#include "beddatasend.h"
#include "beddataprocess.h"
#include "keyboardmange.h"
#include "idatahandler.h"
#include "modbus.h"
#include "bedcontrol.h"
#include "serialportctrl.h"
#include "serialdef.h"
#include "applogger.h"
#include "powercontrol.h"
#include "appsetting.h"
#include "unistd.h"


using namespace SerialPort;

BedControl &BedControl::instance()
{
    static BedControl m_bedControl;
    return m_bedControl;
}


void BedControl::powerOn(void)
{
    m_process->setContentLen(4);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::WRITE_SingleRegister, 0x64, data));
}

void BedControl::powerOff(void)
{
    m_process->setContentLen(4);
    QByteArray data;
    data.append((char)0x00);
    data.append((char)0x00);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::WRITE_SingleRegister, 0x64, data));
}

void BedControl::motorMove(int id, BedControl::MotorDirection direction)
{
    if((id >= 1) && (id <= 8))
    {
        unsigned short address = 0;
        if((id >= 1) && (id <= 4))
            address = 0x66;
        else
            address = 0x65;

        char data[3];
        data[0] = 0x00;
        data[1] = 0x00;

        id  = (id - 1) % 4;

        switch(direction)
        {
        case Forword:
            AppLogger::instance().log()->info(QString("motor: %1, motion: forword.").arg(id));
            data[1] |= (0x01 << (id * 2));
            break;
        case Reversal:
            AppLogger::instance().log()->info(QString("motor: %1, motion: reversal.").arg(id));
            data[1] |= (0x02 << (id * 2));
            break;
        default:
            AppLogger::instance().log()->info(QString("motor: %1, motion: stop.").arg(id));
            break;
        }

        m_process->setContentLen(4);
        QByteArray senddata;
        senddata.append(data[0]);
        senddata.append(data[1]);
        m_send->appendSendData(new BedDataSend::ModbusData(Modbus::WRITE_SingleRegister, address, senddata));
    }
}

void BedControl::motorMove(QList<MotorMove> moves)
{
    QList<MotorMove> group1;
    QList<MotorMove> group2;

    foreach(const MotorMove &index, moves)
    {
        if((index.id >= 1) && (index.id <= 4))
            group1.append(index);
        else if((index.id >= 5) && (index.id <= 6))
            group2.append(index);
    }

    unsigned short address = 0;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x00;

    //process group1
    if(group1.count() > 0)
    {
        address = 0x66;
        foreach(const MotorMove &index, group1)
        {
            int temp = (index.id - 1) % 4;
            switch(index.dir)
            {
            case Forword:
                AppLogger::instance().log()->info(QString("motor: %1, motion: forword.").arg(temp));
                data[1] |= (0x01 << (temp * 2));
                break;
            case Reversal:
                AppLogger::instance().log()->info(QString("motor: %1, motion: reversal.").arg(temp));
                data[1] |= (0x02 << (temp * 2));
                break;
            default:
                AppLogger::instance().log()->info(QString("motor: %1, motion: stop.").arg(temp));
                break;
            }
        }

        m_process->setContentLen(4);
        QByteArray senddata;
        senddata.append(data[0]);
        senddata.append(data[1]);
        m_send->appendSendData(new BedDataSend::ModbusData(Modbus::WRITE_SingleRegister, address, senddata));
    }


    //process group2
    if(group2.count() > 0)
    {
        address = 0x65;
        foreach(const MotorMove &index, group1)
        {
            int temp = (index.id - 1) % 4;
            switch(index.dir)
            {
            case Forword:
                AppLogger::instance().log()->info(QString("motor: %1, motion: forword.").arg(temp));
                data[1] |= (0x01 << (temp * 2));
                break;
            case Reversal:
                AppLogger::instance().log()->info(QString("motor: %1, motion: reversal.").arg(temp));
                data[1] |= (0x02 << (temp * 2));
                break;
            default:
                AppLogger::instance().log()->info(QString("motor: %1, motion: stop.").arg(temp));
                break;
            }
        }

        m_process->setContentLen(4);
        QByteArray senddata;
        senddata.append(data[0]);
        senddata.append(data[1]);
        m_send->appendSendData(new BedDataSend::ModbusData(Modbus::WRITE_SingleRegister, address, senddata));
    }
}

void BedControl::getMotorCurrent() const
{
    m_process->setContentLen(3);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 49, data));
}

void BedControl::getChargeCurrent() const
{
    m_process->setContentLen(3);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 50, data));
}

void BedControl::getDischargeCurrent() const
{
    m_process->setContentLen(3);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 51, data));
}

void BedControl::getHighBatteryVoltage() const
{
    m_process->setContentLen(3);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 53, data));
}

void BedControl::getLowBatteryVoltage() const
{
    m_process->setContentLen(3);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 52, data));
}

void BedControl::getInfusionCount() const
{
    m_process->setContentLen(3);
    m_process->setRegAddress(69);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 69, data));
}

void BedControl::getInfusionSpeed() const
{
    m_process->setContentLen(3);
    m_process->setRegAddress(70);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 70, data));
}

void BedControl::getInfusionMount() const
{
    m_process->setContentLen(3);
    m_process->setRegAddress(71);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 71, data));
}

void BedControl::getWeight() const
{
    m_process->setContentLen(3);
    m_process->setRegAddress(80);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 80, data));
}


BedControl::BedControl() :
    m_modbus(new Modbus(AppSetting::instance().value(AppSetting::ModbusPort).toString())),
    m_process(new BedDataProcess(0x0a)),
    m_dataProcessThread(new QThread),
    m_send(new BedDataSend(this))
{
    m_modbus->init();
    m_modbus->setAddress(0x0a);
    connect(m_modbus, SIGNAL(dataReached(QByteArray)), m_process, SLOT(onProcessData(QByteArray)),
            Qt::QueuedConnection);

    m_process->moveToThread(m_dataProcessThread);
    m_dataProcessThread->start();

    connect(m_process, SIGNAL(infuCountChanged(int)), this, SIGNAL(infuCountChanged(int)), Qt::QueuedConnection);
    connect(m_process, SIGNAL(infuMountChanged(int)), this, SIGNAL(infuMountChanged(int)), Qt::QueuedConnection);
    connect(m_process, SIGNAL(infuSpeedChanged(int)), this, SIGNAL(infuSpeedChanged(int)), Qt::QueuedConnection);
    connect(m_process, SIGNAL(weightChanged(double)), this, SIGNAL(weightChanged(double)), Qt::QueuedConnection);
}

BedControl::~BedControl()
{
    delete m_modbus;
    delete m_dataProcessThread;
    delete m_process;
}


