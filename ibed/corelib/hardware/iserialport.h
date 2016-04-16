#ifndef ISERIALPORT_H
#define ISERIALPORT_H

#include <qglobal.h>
#include <QIODevice>
#include <QMutex>
#include "serialdef.h"
#include "hardware_global.h"


class HARDWARESHARED_EXPORT ISerialPort : public QIODevice
{
public:
    explicit ISerialPort(QObject *parent = 0);
    explicit ISerialPort(const QString &name, QObject *parent = 0);
    virtual ~ISerialPort();

public:
    void setPortName(const QString &name) { m_port = name; }
    inline const QString &portName(void) const { return m_port; }
    bool isSequential() const { return true; }
    inline SerialPort::PortSettings portSettings(void) const { return m_portSettings; }

public:
    virtual bool open(OpenMode mode) = 0;
    virtual void close(void) = 0;
    virtual void flush(void) = 0;
    virtual void startRead(void) = 0;
    virtual void stopRead(void) = 0;


    virtual qint64 bytesAvailable() const = 0;
    virtual bool atEnd() const;

public:
    virtual void setBaudrate(SerialPort::BaudrateType rate) = 0;
    inline SerialPort::BaudrateType baudrate(void) const { return m_portSettings.baudrate; }

    virtual void setDataBits(SerialPort::DataBitsType bits) = 0;
    inline SerialPort::DataBitsType dataBits(void) const { return m_portSettings.dataBits; }

    virtual void setParity(SerialPort::ParityType parity) = 0;
    inline SerialPort::ParityType parity(void) const { return m_portSettings.parity; }

    virtual void setStopBits(SerialPort::StopBitsType bits) = 0;
    inline SerialPort::StopBitsType stopBit(void) const { return m_portSettings.stopBits; }

    virtual void setFlowControl(SerialPort::FlowType flow) = 0;
    inline SerialPort::FlowType flowType(void) const { return m_portSettings.flowControl; }

    virtual void setTimeout(long time) = 0;
    inline long timeout(void) const { return m_portSettings.timeout; }

    virtual void setDtr(bool set = true) = 0;
    virtual void setRts(bool set = true) = 0;
    virtual ulong lineStatus() = 0;

    ulong lastError() const { return m_lastErr; }
    virtual void translateError(ulong error) = 0;
    QString errorString(void) const;



protected:
    QMutex *m_mutex;
    SerialPort::PortSettings m_portSettings;
    ulong m_lastErr;
    QList<unsigned char> m_dataBuffer;
    char m_buffer[128];

protected:
    virtual qint64 readLineData(char *data, qint64 maxlen);
    virtual qint64 readData(char *data, qint64 maxlen) = 0;
    virtual qint64 writeData(const char *data, qint64 len) = 0;

private:
    QString m_port;


private:
    void construct(void);

};

#endif // ISERIALPORT_H
