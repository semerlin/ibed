#include "iserialport.h"

using namespace SerialPort;

ISerialPort::ISerialPort(QObject *parent):
QIODevice(parent),
m_mutex(NULL),
m_lastErr(0)
{
#ifdef Q_OS_LINUX
    setPortName("/dev/ttys0");
#elif Q_OS_WIN32
    setPortName("COM1");
#endif

    m_dataBuffer.clear();
    construct();
}

ISerialPort::ISerialPort(const QString &name, QObject *parent):
QIODevice(parent),
m_mutex(NULL),
m_lastErr(0)
{
    setPortName(name);

    m_dataBuffer.clear();
    construct();
}


ISerialPort::~ISerialPort()
{
    if(m_mutex)
    {
        //need unlock?
//        m_mutex->unlock();

        delete m_mutex;
    }

    m_dataBuffer.clear();
}


void ISerialPort::construct(void)
{
    //default settings
    m_portSettings.baudrate = BAUD9600;
    m_portSettings.dataBits = DATA_8;
    m_portSettings.parity = PAR_NONE;
    m_portSettings.stopBits = STOP_1;
    m_portSettings.flowControl = FLOW_OFF;
    m_portSettings.timeout = 10;

    m_mutex = new QMutex(QMutex::Recursive);

    setOpenMode(QIODevice::NotOpen);
}


qint64 ISerialPort::readLineData(char *data, qint64 maxlen)
{
    if(!data)
        return 0;

    quint64 len = bytesAvailable();
    char *pData = data;

    //length must larger than 1
    if(maxlen < 2)
        return -1;

    //read one byte per time until MIN(len, maxlen), or reach a newline
    while(--len && --maxlen)
    {
        if(-1 == readData(pData, 1))  //an error occured or there is no data to read
            break;
        else
        {
            //end of line?
            if(*pData++ == '\n')
                break;
        }
    }

    *pData = '\0';

    return (pData - data);
}


bool ISerialPort::atEnd() const
{
    if(bytesAvailable())
        return false;

    return true;
}


QString ISerialPort::errorString(void) const
{
    switch(m_lastErr)
    {
    case E_NO_ERROR:
        return QObject::tr("No Error has occurred");
    case E_INVALID_FD:
        return QObject::tr("Invalid file descriptor (port was not opened correctly)");
    case E_NO_MEMORY:
        return QObject::tr("Unable to allocate memory tables (POSIX)");
    case E_CAUGHT_NON_BLOCKED_SIGNAL:
        return QObject::tr("Caught a non-blocked signal (POSIX)");
    case E_PORT_TIMEOUT:
        return QObject::tr("Operation timed out (POSIX)");
    case E_INVALID_DEVICE:
        return QObject::tr("The file opened by the port is not a valid device");
    case E_BREAK_CONDITION:
        return QObject::tr("The port detected a break condition");
    case E_FRAMING_ERROR:
        return QObject::tr("The port detected a framing error (usually caused by incorrect baud rate settings)");
    case E_IO_ERROR:
        return QObject::tr("There was an I/O error while communicating with the port");
    case E_BUFFER_OVERRUN:
        return QObject::tr("Character buffer overrun");
    case E_RECEIVE_OVERFLOW:
        return QObject::tr("Receive buffer overflow");
    case E_RECEIVE_PARITY_ERROR:
        return QObject::tr("The port detected a parity error in the received data");
    case E_TRANSMIT_OVERFLOW:
        return QObject::tr("Transmit buffer overflow");
    case E_READ_FAILED:
        return QObject::tr("General read operation failure");
    case E_WRITE_FAILED:
        return QObject::tr("General write operation failure");
    case E_PERMISSION_DENIED:
        return QObject::tr("Permission denied");
    default:
        return QObject::tr("Unknown error: %1").arg(m_lastErr);
    }
}



