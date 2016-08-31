#include <errno.h>
#include <unistd.h>
#include "posix_serialport.h"
#include "serialdef.h"


/**
***************c_iflag: 输入模式标志，控制终端输入方式*************
* 键值               说明
* IGNBRK            忽略BREAK键输入
* BRKINT            如果设置了IGNBRK，BREAK键输入将被忽略
* IGNPAR            忽略奇偶校验错误
* PARMRK            标识奇偶校验错误
* INPCK             允许输入奇偶校验
* ISTRIP            去除字符的第8个比特
* INLCR             将输入的NL（换行）转换成CR（回车）
* IGNCR             忽略输入的回车
* ICRNL             将输入的回车转化成换行（如果IGNCR未设置的情况下）
* IUCLC             将输入的大写字符转换成小写字符（非POSIX）
* IXON              允许输出时对XON/XOFF流进行控制
* IXANY             输入任何字符将重启停止的输出
* IXOFF             允许输入时对XON/XOFF流进行控制
* IMAXBEL           当输入队列满的时候开始响铃
*
***************c_oflag: 输出模式标志，控制终端输出方式**************
* 键值                 说明
* OPOST               处理后输出
* OLCUC               将输入的小写字符转换成大写字符（非POSIX）
* ONLCR               将输入的NL（换行）转换成CR（回车）及NL（换行）
* OCRNL               将输入的CR（回车）转换成NL（换行）
* ONOCR               第一行不输出回车符
* ONLRET              不输出回车符
* OFILL               发送填充字符以延迟终端输出
* OFDEL               以 ASCII的DEL作为填充字符，如果未设置该参数，填充字符为NUL
* NLDLY               换行输出延时，可以取NL0（不延迟）或NL1（延迟0.1s）
* CRDLY               回车延迟，取值范围为：CR0、CR1、CR2和 CR3
* TABDLY              水平制表符输出延迟，取值范围为：TAB0、TAB1、TAB2和TAB3
* BSDLY               空格输出延迟，可以取BS0或BS1
* VTDLY               垂直制表符输出延迟，可以取VT0或VT1
* FFDLY               换页延迟，可以取FF0或FF1
*
**************c_cflag：控制模式标志，指定终端硬件控制信息************
* 键 值                  说 明
* CBAUD                 波特率（4+1位）（非POSIX）
* CBAUDEX               附加波特率（1位）（非POSIX）
* CSIZE                 字符长度，取值范围为CS5、CS6、CS7或CS8
* CSTOPB                设置两个停止位
* CREAD                 使用接收器
* PARENB                使用奇偶校验
* PARODD                对输入使用奇偶校验，对输出使用偶校验
* HUPCL                 关闭设备时挂起
* CLOCAL                忽略调制解调器线路状态
* CRTSCTS               使用RTS/CTS流控制
*
***************c_lflag：本地模式标志，控制终端编辑功能***************
* 键 值                    说 明
* ISIG                    当输入INTR、QUIT、SUSP或DSUSP时，产生相应的信号
* ICANON                  使用标准输入模式
* XCASE                   在 ICANON和XCASE同时设置的情况下，终端只使用大写。
* ECHO                    显示输入字符
* ECHOE                   如果ICANON同时设置，ERASE将删除输入的字符
* ECHOK                   如果ICANON同时设置，KILL将删除当前行
* ECHONL                  如果ICANON同时设置，即使ECHO没有设置依然显示换行符
* ECHOPRT                 如果ECHO和ICANON同时设置，将删除打印出的字符（非POSIX）
* TOSTOP                  向后台输出发送SIGTTOU信号
*
******c_cc[NCCS]：控制字符，用于保存终端驱动程序中的特殊字符，如输入结束符等****
*
* 宏                        说 明
* VINTR                     Interrupt字符
* VEOL                      附加的End-of-file字符
* VQUIT                     Quit字符
* VTIME                     非规范模式读取时的超时时间
* VERASE                    Erase字符
* VSTOP                     Stop字符
* VKILL                     Kill字符
* VSTART                    Start字符
* VEOF                      End-of-file字符
* VSUSP                     Suspend字符
* VMIN                      非规范模式读取时的最小字符数
*
* tcsetattr函数用于设置终端的相关参数。
* fd为打开的终端文件描述符
* optional_actions用于控制修改起作用的时间
* termios_p中保存了要修改的参数
*
* optional_actions可以取如下的值:
* TCSANOW: 不等数据传输完毕就立即改变属性。
* TCSADRAIN: 等待所有数据传输结束才改变属性。
* TCSAFLUSH: 清空输入输出缓冲区才改变属性。
*
* 错误信息：
* EBADF: 非法的文件描述符。
* EINTR: tcsetattr函数调用被信号中断。
* EINVAL: 参数optional_actions使用了非法值，或参数termios中使用了非法值。
* ENCTTY: 非终端的文件描述符。
*
*
**/



using namespace SerialPort;


Posix_SerialPort::Posix_SerialPort(QObject *parent):
ISerialPort(parent),
m_fd(-1),
m_notifier(NULL)
{

}

Posix_SerialPort::Posix_SerialPort(const Posix_SerialPort& s, QObject *parent):
ISerialPort(parent),
m_fd(-1),
m_notifier(NULL)
{
    setPortName(s.portName());
    m_portSettings = s.portSettings();
    m_lastErr = s.lastError();
    m_termios = s.m_termios;
}

Posix_SerialPort::Posix_SerialPort(const QString &name, QObject *parent):
ISerialPort(name, parent),
m_fd(-1),
m_notifier(NULL)
{

}

Posix_SerialPort::Posix_SerialPort(const SerialPort::PortSettings &settings, QObject *parent):
ISerialPort(parent),
m_fd(-1),
m_notifier(NULL)
{
    m_portSettings = settings;

}

Posix_SerialPort::Posix_SerialPort(const QString &name, const SerialPort::PortSettings &settings, QObject *parent):
ISerialPort(name, parent),
m_fd(-1),
m_notifier(NULL)
{
    m_portSettings = settings;
}

Posix_SerialPort& Posix_SerialPort::operator=(const Posix_SerialPort &s)
{
    setPortName(s.portName());
    m_portSettings = s.portSettings();
    m_lastErr = s.lastError();
    m_termios = s.m_termios;

    return *this;
}

Posix_SerialPort::~Posix_SerialPort()
{
    if(m_fd)
        ::close(m_fd);


    if(m_notifier)
    {
        delete m_notifier;
        m_notifier = NULL;
    }
}

/**
 * @brief 枚举系统中可用的串口
 * @return 可用的串口名
 */
QStringList Posix_SerialPort::enumPorts(void) const
{
    //清除原有空间
    m_portNames.clear();

    //枚举系统中可用的串口
    m_portNames << "ttyS1";
    return m_portNames;
}

bool Posix_SerialPort::open(OpenMode mode)
{
    m_mutex->lock();

    //串口已经打开
    if(!isOpen())
    {
        /**
        * O_NOCTTY可以告诉系统这个程序不会成为这个端口上的“控制终端”。
        * 如果不这样做的话，所有的输入，比如键盘上过来的Ctrl+C中止信号等等，会影响到你的进程。

        * O_NDELAY标志则是告诉系统，这个程序并不关心DCD信号线的状态——也就是不关心端口另一端是否已经连接。
        * 如果不指定这个标志的话，除非DCD信号线上有space电压否则这个程序会一直睡眠。
        **/

        if((m_fd = ::open(portName().toLatin1().data(), O_RDWR | O_NOCTTY | O_NDELAY)) != -1)
        {
			setOpenMode(mode);
            ::tcgetattr(m_fd, &m_termios);
            //串口可读
            m_termios.c_cflag |= (CLOCAL | CREAD);

            //输入输出模式
            m_termios.c_lflag &= (~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ISIG));
            m_termios.c_iflag &= (~(INPCK | IGNPAR | PARMRK | ISTRIP | ICRNL | IXANY));
            m_termios.c_oflag &= (~OPOST);

            //设置最小读取位
            m_termios.c_cc[VMIN] = 0;
            m_termios.c_cc[VINTR] = _POSIX_VDISABLE;
            m_termios.c_cc[VQUIT] = _POSIX_VDISABLE;
            m_termios.c_cc[VSTART] = _POSIX_VDISABLE;
            m_termios.c_cc[VSTOP] = _POSIX_VDISABLE;
            m_termios.c_cc[VSUSP] = _POSIX_VDISABLE;


            setBaudrate(m_portSettings.baudrate);
            setDataBits(m_portSettings.dataBits);
            setParity(m_portSettings.parity);
            setStopBits(m_portSettings.stopBits);
            setFlowControl(m_portSettings.flowControl);
            setTimeout(m_portSettings.timeout);

            //设置新的状态
            if(::tcsetattr(m_fd, TCSAFLUSH, &m_termios) != 0)
            {
                translateError(errno);
                ::close(m_fd);
                m_mutex->unlock();
                setOpenMode(NotOpen);
                return false;
            }


            if(m_notifier)
            {
                disconnect(m_notifier, SIGNAL(activated(int)), this, SLOT(autoRead()));
                delete m_notifier;
            }

            m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
            connect(m_notifier, SIGNAL(activated(int)), this, SLOT(autoRead()));

            m_mutex->unlock();
            return true;
        }
        else
        {
            translateError(errno);
            m_mutex->unlock();
            return false;
        }
    }

    m_mutex->unlock();
    return isOpen();
}

void Posix_SerialPort::close()
{
    m_mutex->lock();

    if(m_notifier)
    {
        disconnect(m_notifier, SIGNAL(activated(int)), this, SLOT(autoRead()));
        delete m_notifier;
        m_notifier = NULL;
    }

    if(isOpen())
    {
        flush();
        ::close(m_fd);
        setOpenMode(QIODevice::NotOpen);
        m_fd = -1;
    }

    m_mutex->unlock();
}


void Posix_SerialPort::resume(void)
{
    m_mutex->lock();

    if(isOpen())
        connect(m_notifier, SIGNAL(activated(int)), this, SLOT(autoRead()));

    m_mutex->unlock();
}

void Posix_SerialPort::suspend(void)
{
    m_mutex->lock();

    if(isOpen())
        disconnect(m_notifier, SIGNAL(activated(int)), this, SLOT(autoRead()));

    m_mutex->unlock();
}

bool Posix_SerialPort::waitForBytesWritten(int msecs)
{
    Q_UNUSED(msecs)
    m_mutex->lock();
    ::tcdrain(m_fd);
    m_mutex->unlock();
    return true;
}

void Posix_SerialPort::flush()
{
    m_mutex->lock();
    ::tcdrain(m_fd);
    m_dataBuffer.clear();
    m_mutex->unlock();
}

/*
qint64 Posix_SerialPort::bytesAvailable() const
{
    m_mutex->lock();

    int tempBytes;


    if (::ioctl(m_fd, FIONREAD, &tempBytes) == -1)
    {
        m_mutex->unlock();
        return (qint64)-1;
    }

    tempBytes += m_dataBuffer.size();

    m_mutex->unlock();

    return tempBytes;
}


qint64 Posix_SerialPort::readData(char *data, qint64 maxlen)
{
    // TODO 效率测试
    m_mutex->lock();

    char *pdata = data;
    int size = m_dataBuffer.size();
    if(!size || !maxlen)
        return 0;

    while(--size && --maxlen)
    {
        *pdata++ = m_dataBuffer.first();
        m_dataBuffer.pop_front();
    }

    m_mutex->unlock();

    return (pdata - data);
}
*/

qint64 Posix_SerialPort::bytesAvailable() const
{
    m_mutex->lock();

    int tempBytes = 0;

    if (::ioctl(m_fd, FIONREAD, &tempBytes) == -1)
    {
        m_mutex->unlock();
        return (qint64)-1;
    }

    m_mutex->unlock();

    return tempBytes;
}


qint64 Posix_SerialPort::readData(char *data, qint64 maxlen)
{
    m_mutex->lock();

    int retVal = ::read(m_fd, data, maxlen);
    if(-1 == retVal)
        m_lastErr = E_READ_FAILED;

    m_mutex->unlock();

    return retVal;
}

qint64 Posix_SerialPort::writeData(const char *data, qint64 len)
{
    m_mutex->lock();

    int retVal = ::write(m_fd, data, len);
    if(-1 == retVal)
        m_lastErr = E_WRITE_FAILED;

    m_mutex->unlock();

    return retVal;
}



void Posix_SerialPort::setBaudrate(SerialPort::BaudrateType rate)
{
    m_mutex->lock();

    m_portSettings.baudrate = rate;


    if(isOpen())
    {
        //设置波特率
        switch(m_portSettings.baudrate)
        {
        case BAUD50:
            ::cfsetispeed(&m_termios, B50);
            ::cfsetospeed(&m_termios, B50);
            break;
        case BAUD75:
            ::cfsetispeed(&m_termios, B75);
            ::cfsetospeed(&m_termios, B75);
            break;
        case BAUD110:
            ::cfsetispeed(&m_termios, B110);
            ::cfsetospeed(&m_termios, B110);
            break;
        case BAUD134:
            ::cfsetispeed(&m_termios, B134);
            ::cfsetospeed(&m_termios, B134);
            break;
        case BAUD150:
            ::cfsetispeed(&m_termios, B150);
            ::cfsetospeed(&m_termios, B150);
            break;
        case BAUD200:
            ::cfsetispeed(&m_termios, B200);
            ::cfsetospeed(&m_termios, B200);
            break;
        case BAUD300:
            ::cfsetispeed(&m_termios, B300);
            ::cfsetospeed(&m_termios, B300);
            break;
        case BAUD600:
            ::cfsetispeed(&m_termios, B600);
            ::cfsetospeed(&m_termios, B600);
            break;
        case BAUD1200:
            ::cfsetispeed(&m_termios, B1200);
            ::cfsetospeed(&m_termios, B1200);
            break;
        case BAUD1800:
            ::cfsetispeed(&m_termios, B1800);
            ::cfsetospeed(&m_termios, B1800);
            break;
        case BAUD2400:
            ::cfsetispeed(&m_termios, B2400);
            ::cfsetospeed(&m_termios, B2400);
            break;
        case BAUD4800:
            ::cfsetispeed(&m_termios, B4800);
            ::cfsetospeed(&m_termios, B4800);
            break;
        case BAUD9600:
            ::cfsetispeed(&m_termios, B9600);
            ::cfsetospeed(&m_termios, B9600);
            break;
        case BAUD19200:
            ::cfsetispeed(&m_termios, B19200);
            ::cfsetospeed(&m_termios, B19200);
            break;
        case BAUD38400:
            ::cfsetispeed(&m_termios, B38400);
            ::cfsetospeed(&m_termios, B38400);
            break;
        case BAUD57600:
            ::cfsetispeed(&m_termios, B57600);
            ::cfsetospeed(&m_termios, B57600);
            break;
        case BAUD115200:
            ::cfsetispeed(&m_termios, B115200);
            ::cfsetospeed(&m_termios, B115200);
            break;
        default:
            ::cfsetispeed(&m_termios, B9600);
            ::cfsetospeed(&m_termios, B9600);
            break;
        }

        ::tcsetattr(m_fd, TCSAFLUSH, &m_termios);
    }

    m_mutex->unlock();
}

void Posix_SerialPort::setDataBits(SerialPort::DataBitsType bits)
{
    m_mutex->lock();

    m_portSettings.dataBits = bits;

    if(isOpen())
    {
        //设置数据位
        m_termios.c_cflag &= ~CSIZE;
        switch(m_portSettings.dataBits)
        {
        case DATA_5:
            m_termios.c_cflag |= CS5;
            break;
        case DATA_6:
            m_termios.c_cflag |= CS6;
            break;
        case DATA_7:
            m_termios.c_cflag |= CS7;
            break;
        case DATA_8:
            m_termios.c_cflag |= CS8;
            break;
        default:
            m_termios.c_cflag |= CS8;
            break;
        }

        ::tcsetattr(m_fd, TCSAFLUSH, &m_termios);
    }

    m_mutex->unlock();
}

void Posix_SerialPort::setParity(SerialPort::ParityType parity)
{
    m_mutex->lock();

    m_portSettings.parity = parity;

    if(isOpen())
    {
        //设置校验位
        switch(m_portSettings.parity)
        {
        case PAR_NONE:
            m_termios.c_cflag &= ~PARENB;
            m_termios.c_iflag &= ~INPCK;
            break;
        case PAR_EVEN:
            m_termios.c_cflag &= (~PARODD);
            m_termios.c_cflag |= PARENB;
            m_termios.c_iflag |= INPCK;
            break;
        case PAR_ODD:
            m_termios.c_cflag |= (PARENB | PARODD);
            m_termios.c_iflag |= INPCK;
            break;
        case PAR_SPACE:
            m_termios.c_cflag &= ~PARENB;
            m_termios.c_cflag &= ~CSTOPB;
            break;
        default:
            m_termios.c_cflag &= ~PARENB;
            break;
        }
        ::tcsetattr(m_fd, TCSAFLUSH, &m_termios);
    }

    m_mutex->unlock();
}

void Posix_SerialPort::setStopBits(SerialPort::StopBitsType bits)
{
    m_mutex->lock();

    m_portSettings.stopBits = bits;

    if(isOpen())
    {
        //设置停止位
        switch(m_portSettings.stopBits)
        {
        case STOP_1:
            m_termios.c_cflag &= ~CSTOPB;
            break;
        case STOP_2:
            m_termios.c_cflag |= CSTOPB;
            break;
        default:
            m_termios.c_cflag &= ~CSTOPB;
            break;
        }

        ::tcsetattr(m_fd, TCSAFLUSH, &m_termios);
    }

    m_mutex->unlock();
}

void Posix_SerialPort::setFlowControl(SerialPort::FlowType flow)
{
    m_mutex->lock();

    m_portSettings.flowControl = flow;

    if(isOpen())
    {
        //设置流控制
        switch(m_portSettings.flowControl)
        {
        case FLOW_OFF:
            m_termios.c_cflag &= (~CRTSCTS);
            m_termios.c_iflag &= (~(IXON | IXOFF | IXANY));
            break;
        case FLOW_HARDWARE:
            m_termios.c_cflag |= CRTSCTS;
            m_termios.c_iflag &= (~(IXON | IXOFF | IXANY));
            break;
        case FLOW_XONXOFF:
            m_termios.c_cflag &= (~CRTSCTS);
            m_termios.c_iflag |= (IXON | IXOFF | IXANY);
            break;
        default:
            break;
        }

        ::tcsetattr(m_fd, TCSAFLUSH, &m_termios);
    }

    m_mutex->unlock();
}

void Posix_SerialPort::setTimeout(long time)
{
    m_mutex->lock();

    m_portSettings.timeout = time;

    if(isOpen())
    {
        m_termios.c_cc[VTIME] = m_portSettings.timeout / 100;
        ::tcsetattr(m_fd, TCSAFLUSH, &m_termios);
    }

    m_mutex->unlock();
}

void Posix_SerialPort::setDtr(bool set)
{
    m_mutex->lock();

    if(isOpen())
    {
        int status;
        ::ioctl(m_fd, TIOCMGET, &status);
        if(set)
            status |= TIOCM_DTR;
        else
            status &= ~TIOCM_DTR;
        ::ioctl(m_fd, TIOCMSET, &status);
    }

    m_mutex->unlock();
}

void Posix_SerialPort::setRts(bool set)
{
    m_mutex->lock();

    if(isOpen())
    {
        int status;
        ::ioctl(m_fd, TIOCMGET, &status);
        if(set)
            status |= TIOCM_RTS;
        else
            status &= ~TIOCM_RTS;
        ::ioctl(m_fd, TIOCMSET, &status);
    }

    m_mutex->unlock();
}

ulong Posix_SerialPort::lineStatus(void)
{
    m_mutex->lock();

    ulong status = 0;

    if(isOpen())
    {
        ulong temp = 0;
        ::ioctl(m_fd, TIOCMGET, &temp);

        if(temp & TIOCM_CTS)
            status |= LS_CTS;
        if(temp & TIOCM_DSR)
            status |= LS_DSR;
        if(temp & TIOCM_RI)
            status |= LS_RI;
        if(temp & TIOCM_CD)
            status |= LS_DCD;
        if(temp & TIOCM_DTR)
            status |= LS_DTR;
        if(temp & TIOCM_RTS)
            status |= LS_RTS;
        if(temp & TIOCM_ST)
            status |= LS_ST;
        if(temp & TIOCM_SR)
            status |= LS_SR;
    }

    m_mutex->unlock();

    return status;
}

void Posix_SerialPort::translateError(ulong error)
{
    switch(error)
    {
    case ENOENT:
        m_lastErr = E_INVALID_DEVICE;
        break;
    case EIO:
        m_lastErr = E_IO_ERROR;
        break;
    case EBADF:
    case ENOTTY:
        m_lastErr = E_INVALID_FD;
        break;
    case EINTR:
        m_lastErr = E_CAUGHT_NON_BLOCKED_SIGNAL;
        break;
    case ENOMEM:
        m_lastErr = E_NO_MEMORY;
        break;
    case EACCES:
        m_lastErr = E_PERMISSION_DENIED;
        break;
    }
}

/*
void Posix_SerialPort::autoRead(void)
{
    m_mutex->lock();

    int tempLen = 0;
    if (::ioctl(m_fd, FIONREAD, &tempLen) == -1)
    {
        m_lastErr = E_READ_FAILED;
        m_mutex->unlock();
        return ;
    }

    int retVal = ::read(m_fd, m_buffer, sizeof(m_buffer));
    if(-1 == retVal)
        m_lastErr = E_READ_FAILED;
    else
    {
        for(int i = 0; i < retVal; i++)
            m_dataBuffer.append(m_buffer[i]);
    }

    m_mutex->unlock();

    emit dataReached();
}
*/

void Posix_SerialPort::autoRead(void)
{
    emit dataReady();
}

