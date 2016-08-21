#include <QMutex>
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
#include "crc.h"


using namespace SerialPort;

BedControl &BedControl::instance()
{
    static BedControl m_bedControl;
    return m_bedControl;
}

quint8 BedControl::weight() const
{
#ifdef TARFET_IMX
    PowerControl::instance().rs485DirectCtrl(1);
#endif

//    m_code = Modbus::READ_InputRegister;
    m_contentLen = 2;
    char data[3];
    data[0] = 0x00;
    data[1] = 0x01;
    m_modbus->write(Modbus::READ_InputRegister, 0x79, data, 2);

#ifdef TARGET_IMX
    PowerControl::instance().rs485DirectCtrl(0);
#endif
}

void BedControl::powerOn(void)
{
#ifdef TARFET_IMX
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
            data[1] |= (0x01 << (id * 2));
            break;
        case Reversal:
            data[1] |= (0x02 << (id * 2));
            break;
        default:
            break;
        }
        m_modbus->write(Modbus::WRITE_SingleRegister, address, data, 2);
    }

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


BedControl::BedControl() :
    m_modbus(new Modbus(AppSetting::instance().value(AppSetting::ModbusPort).toString())),
    m_mutex(new QMutex),
    m_contentLen(0)
{
    m_modbus->init();
    m_modbus->setAddress(m_address);
    connect(m_modbus, SIGNAL(dataReached(QByteArray)), this, SLOT(onDataReached(QByteArray)));

    addDataHandler(new WeightDataHandler(0x04, 0x79));
}

BedControl::~BedControl()
{
    delete m_modbus;
}


