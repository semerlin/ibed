#include "bedcontrol.h"
#include "serialportctrl.h"
#include "serialdef.h"
#include "applogger.h"
#include <QDebug>
#include "powercontrol.h"


using namespace SerialPort;

BedControl &BedControl::instance()
{
    static BedControl m_bedControl;
    return m_bedControl;
}

void BedControl::powerOn(void)
{
    PowerControl::instance().rs485DirectCtrl(1);
    char data[20];
    data[0] = 0x0a;
    data[1] = 0x06;
    data[2] = 0x00;
    data[3] = 0x64;
    data[4] = 0x00;
    data[5] = 0x01;
    data[6] = 0x08;
    data[7] = 0xae;

    m_serial->write(data, 8);

    char data1[20];
    data1[0] = 0x0a;
    data1[1] = 0x06;
    data1[2] = 0x00;
    data1[3] = 0x66;
    data1[4] = 0x00;
    data1[5] = 0x01;
    data1[6] = 0xa9;
    data1[7] = 0x6e;

    m_serial->write(data, 8);

    PowerControl::instance().rs485DirectCtrl(0);
//    PowerControl::instance().rs485DirectCtrl(0);
}

void BedControl::powerOff(void)
{

}

void BedControl::onDataReached()
{
    qDebug() << "data reached: " << m_serial->bytesAvailable();
    QByteArray data = m_serial->read(m_serial->bytesAvailable());
    for(int i = 0; i < data.count(); i++)
        qDebug() << "value: " << QString::number(data.at(i));
}



BedControl::BedControl() :
    m_serial(new SerialPortCtrl)
{
//#ifdef TARGET_IMX
    m_serial->setPortName("/dev/ttySP1");
//#else
//    m_serial->setPortName("/dev/ttyUSB0");
//#endif

    m_serial->setBaudrate(BAUD115200);
    m_serial->setDataBits(DATA_8);
    m_serial->setParity(PAR_NONE);
    m_serial->setStopBits(STOP_1);

    //open bed control serial port
    if(m_serial->open(QIODevice::ReadWrite))
    {
        AppLogger::instance().log()->info(QT_TRANSLATE_NOOP("Sensor",
                                                            QString("open serial port '%1' success").
                                                            arg(m_serial->portName())));

        bool flag = connect(m_serial, SIGNAL(dataReached()), this, SLOT(onDataReached()));
        flag = false;
    }
    else
    {
        AppLogger::instance().log()->info(QT_TRANSLATE_NOOP("Sensor",
                                                            QString("open serial port '%1' failed!--%2").
                                                            arg(m_serial->portName()).
                                                            arg(m_serial->errorString())));
    }
}

BedControl::~BedControl()
{
    delete m_serial;
}


