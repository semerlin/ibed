#include <QMutex>
#include "keyboardmange.h"
#include "idatahandler.h"
#include "modbus.h"
#include "bedcontrol.h"
#include "serialportctrl.h"
#include "serialdef.h"
#include "applogger.h"
#include "powercontrol.h"
#include "appsetting.h"
#include "boost/foreach.hpp"
#include "weightdatahandler.h"
#include "infucountdatahandler.h"
#include "infumountdatahandler.h"
#include "infuspeeddatahandler.h"
#include "crc.h"


using namespace SerialPort;

BedControl &BedControl::instance()
{
    static BedControl m_bedControl;
    return m_bedControl;
}

void BedControl::addDataHandler(IDataHandler *handler)
{
    if(handler != NULL)
        m_handlers.append(handler);
}


void BedControl::powerOn(void)
{
#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

    m_contentLen = 2;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x01;
    m_modbus->write(Modbus::WRITE_SingleRegister, 0x64, data, 2);

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::powerOff(void)
{
#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

    m_contentLen = 2;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x00;
    m_modbus->write(Modbus::WRITE_SingleRegister, 0x64, data, 2);

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::motorMove(int id, BedControl::MotorDirection direction)
{
#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

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
        m_modbus->write(Modbus::WRITE_SingleRegister, address, data, 2);
    }

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::getMotorCurrent() const
{
#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

    m_contentLen = 2;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x01;
    m_modbus->write(Modbus::READ_InputRegister, 0x49, data, 2);

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::getChargeCurrent() const
{
#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

    m_contentLen = 2;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x01;
    m_modbus->write(Modbus::READ_InputRegister, 0x50, data, 2);

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::getDischargeCurrent() const
{
#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

    m_contentLen = 2;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x01;
    m_modbus->write(Modbus::READ_InputRegister, 0x51, data, 2);

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::getHighBatteryVoltage() const
{
#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

    m_contentLen = 2;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x01;
    m_modbus->write(Modbus::READ_InputRegister, 0x53, data, 2);

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::getLowBatteryVoltage() const
{
#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

    m_contentLen = 2;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x01;
    m_modbus->write(Modbus::READ_InputRegister, 0x52, data, 2);

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::getInfusionCount() const
{
#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

    m_contentLen = 2;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x01;
    m_modbus->write(Modbus::READ_InputRegister, 0x69, data, 2);

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::getInfusionSpeed() const
{
#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

    m_contentLen = 2;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x01;
    m_modbus->write(Modbus::READ_InputRegister, 0x70, data, 2);

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::getInfusionMount() const
{
#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

    m_contentLen = 2;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x01;
    m_modbus->write(Modbus::READ_InputRegister, 0x71, data, 2);

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::getWeight() const
{
#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

    m_contentLen = 2;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x01;
    m_modbus->write(Modbus::READ_InputRegister, 0x79, data, 2);

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::onDataReached(const QByteArray &data)
{
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
            validData = m_data.remove(0, m_contentLen + 6);
            m_mutex->unlock();

            //check CRC
            quint16 crc = CRC::mbCRC16((quint8 *)validData.data(), m_contentLen + 4);
            quint16 rCrc = validData.at(m_contentLen + 5);
            rCrc <<= 8;
            rCrc += validData.at(m_contentLen + 4) ;
            if(crc == rCrc)
            {
                //find handler
                quint8 fucCode = m_data.at(1);
                quint16 regAddress = m_data.at(2);
                regAddress <<= 8;
                regAddress += m_data.at(3);
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

void BedControl::onKeyPressed(int id)
{
    if(((id + 1) % 2) == 0)
    {
        motorMove(id, Forword);
    }
    else
    {
        motorMove(id, Reversal);
    }
}

void BedControl::onKeyReleased(int id)
{
    motorMove(id, Stop);
}


BedControl::BedControl() :
    m_modbus(new Modbus(AppSetting::instance().value(AppSetting::ModbusPort).toString())),
    m_mutex(new QMutex),
    m_contentLen(0)
{
    m_modbus->init();
    m_modbus->setAddress(m_address);
    connect(m_modbus, SIGNAL(dataReached(QByteArray)), this, SLOT(onDataReached(QByteArray)));

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


#ifdef TARGET_IMX
    m_kbdMange = new KeyboardMange;
    m_kbdMange->init();
    connect(m_kbdMange, SIGNAL(keyPressed(int)), this, SLOT(onKeyPressed(int)));
    connect(m_kbdMange, SIGNAL(keyReleased(int)), this, SLOT(onKeyReleased(int)));
#endif
}

BedControl::~BedControl()
{
    delete m_modbus;
}


