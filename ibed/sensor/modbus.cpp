#include "modbus.h"
#include "serialportctrl.h"
#include "applogger.h"
#include "crc.h"

Modbus::Modbus(const QString &portName) :
    m_serial(new SerialPortCtrl),
    m_port(portName),
    m_address(0x00)
{

}

Modbus::~Modbus()
{
    delete m_serial;
}


bool Modbus::init(void) const
{
    m_serial->setPortName(m_port);
    m_serial->setBaudrate(SerialPort::BAUD19200);
    m_serial->setDataBits(SerialPort::DATA_8);
    m_serial->setParity(SerialPort::PAR_NONE);
    m_serial->setStopBits(SerialPort::STOP_1);
    m_serial->setFlowControl(SerialPort::FLOW_OFF);
    m_serial->setDtr(false);
    m_serial->setRts(false);

    //open bed control serial port
    if(m_serial->open(QIODevice::ReadWrite))
    {
        AppLogger::instance().log()->info(QT_TRANSLATE_NOOP("Sensor",
                                                            QString("open serial port '%1' success").
                                                            arg(m_serial->portName())));

        connect(m_serial, SIGNAL(dataReady()), this, SLOT(onDataReached()));
    }
    else
    {
        AppLogger::instance().log()->info(QT_TRANSLATE_NOOP("Sensor",
                                                            QString("open serial port '%1' failed!--%2").
                                                            arg(m_serial->portName()).
                                                            arg(m_serial->errorString())));

        return false;
    }

    return true;

}

void Modbus::setAddress(unsigned char address)
{
    m_address = address;
}

void Modbus::write(Modbus::FunctionCode code, unsigned short address, const char *data, int len)
{
    QByteArray sendData;
    sendData.append(m_address);
    sendData.append(code);
    sendData.append(address >> 8);
    sendData.append(address & 0xff);
    for(int i = 0; i < len; ++i)
        sendData.append(data[i]);

    unsigned short crc = CRC::mbCRC16((unsigned char *)sendData.data(), sendData.count());

    sendData.append(crc & 0xff);
    sendData.append(crc >> 8);

    m_serial->write(sendData);
    m_serial->waitForBytesWritten(10);
}

void Modbus::write(Modbus::FunctionCode code, unsigned short address, const QByteArray &data)
{
    write(code, address, data.data(), data.count());
}

void Modbus::onDataReached()
{
    QByteArray data = m_serial->read(m_serial->bytesAvailable());
    emit dataReached(data);
}
