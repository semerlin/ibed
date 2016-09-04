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
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

    m_process->setContentLen(4);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::WRITE_SingleRegister, 0x64, data));

//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
}

void BedControl::powerOff(void)
{
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

    m_process->setContentLen(4);
    QByteArray data;
    data.append((char)0x00);
    data.append((char)0x00);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::WRITE_SingleRegister, 0x64, data));

//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
}

void BedControl::motorMove(int id, BedControl::MotorDirection direction)
{
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

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

//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
}

void BedControl::motorMove(QList<int> id, BedControl::MotorDirection direction)
{
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

    QSet<int> group1;
    QSet<int> group2;

    foreach(const int &index, id)
    {
        if((index >= 1) && (index <= 4))
            group1.insert(index);
        else if((index >= 5) && (index <= 6))
            group2.insert(index);
    }

    unsigned short address = 0;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x00;

    //process group1
    if(group1.count() > 0)
    {
        address = 0x66;
        foreach(const int &index, group1)
        {
            int temp = (index - 1) % 4;
            switch(direction)
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
        foreach(const int &index, group1)
        {
            int temp = (index - 1) % 4;
            switch(direction)
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


//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
}

void BedControl::getMotorCurrent() const
{
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

    m_process->setContentLen(3);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 49, data));

//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
}

void BedControl::getChargeCurrent() const
{
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

    m_process->setContentLen(3);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 50, data));

//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
}

void BedControl::getDischargeCurrent() const
{
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

    m_process->setContentLen(3);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 51, data));

//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
}

void BedControl::getHighBatteryVoltage() const
{
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

    m_process->setContentLen(3);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 53, data));

//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
}

void BedControl::getLowBatteryVoltage() const
{
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

    m_process->setContentLen(3);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 52, data));

//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
}

void BedControl::getInfusionCount() const
{
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

    m_process->setContentLen(3);
    m_process->setRegAddress(69);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 69, data));

//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
}

void BedControl::getInfusionSpeed() const
{
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

    m_process->setContentLen(3);
    m_process->setRegAddress(70);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 70, data));

//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
}

void BedControl::getInfusionMount() const
{
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

    m_process->setContentLen(3);
    m_process->setRegAddress(71);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 71, data));

//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
}

void BedControl::getWeight() const
{
//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(1);
//#endif

    m_process->setContentLen(3);
    m_process->setRegAddress(80);
    QByteArray data;
    data.append((char)0x00);
    data.append(0x01);
    m_send->appendSendData(new BedDataSend::ModbusData(Modbus::READ_InputRegister, 80, data));

//#ifdef TARGET_IMX
//    PowerControl::instance().rs485DirectCtrl(0);
//#endif
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

    connect(m_process, SIGNAL(infuCountChanged(int)), this, SIGNAL(infuCountChanged(int)));
    connect(m_process, SIGNAL(infuMountChanged(int)), this, SIGNAL(infuMountChanged(int)));
    connect(m_process, SIGNAL(infuSpeedChanged(int)), this, SIGNAL(infuSpeedChanged(int)));
    connect(m_process, SIGNAL(weightChanged(double)), this, SIGNAL(weightChanged(double)));
}

BedControl::~BedControl()
{
    delete m_modbus;
    delete m_dataProcessThread;
    delete m_process;
}


