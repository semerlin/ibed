#ifndef POSIX_SERIALPORT_H
#define POSIX_SERIALPORT_H

#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <QSocketNotifier>
#include "iserialport.h"




class SENSORSHARED_EXPORT Posix_SerialPort : public ISerialPort
{
    Q_OBJECT

public:
    explicit Posix_SerialPort(QObject *parent = 0);
    explicit Posix_SerialPort(const Posix_SerialPort& s, QObject *parent = 0);
    explicit Posix_SerialPort(const QString &name, QObject *parent = 0);
    explicit Posix_SerialPort(const SerialPort::PortSettings &settings, QObject *parent = 0);
    explicit Posix_SerialPort(const QString &name, const SerialPort::PortSettings &settings, QObject *parent = 0);
    ~Posix_SerialPort();


public:
    Posix_SerialPort& operator=(const Posix_SerialPort &s);

public:
    QStringList enumPorts(void) const;

public:
    bool open(OpenMode mode);
    void close(void);
    void flush(void);
    void resume(void);
    void suspend(void);

    qint64 bytesAvailable() const;

public slots:
    void setBaudrate(SerialPort::BaudrateType rate);
    void setDataBits(SerialPort::DataBitsType bits);
    void setParity(SerialPort::ParityType parity);
    void setStopBits(SerialPort::StopBitsType bits);
    void setFlowControl(SerialPort::FlowType flow);
    void setTimeout(long time);
    void setDtr(bool set = true);
    void setRts(bool set = true);
    ulong lineStatus();
    void translateError(ulong error);


protected:
    struct termios m_termios;
    int m_fd;

protected:
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);



private slots:
    void autoRead(void);

private:
    int test;
    QSocketNotifier *m_notifier;
};

#endif // Posix_SerialPort_H
