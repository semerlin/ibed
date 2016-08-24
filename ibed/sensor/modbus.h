#ifndef MODBUS_H
#define MODBUS_H

#include <QObject>

class SerialPortCtrl;

class Modbus : public QObject
{
    Q_OBJECT
public:
    typedef enum
    {
        READ_InputRegister = 0x04,
        WRITE_SingleRegister = 0x06,

        Invalid = 0xff,
    }FunctionCode;

public:
    Modbus(const QString &portName);
    ~Modbus();

public:
    bool init(void) const;
    void setAddress(unsigned char address);

    void write(Modbus::FunctionCode code, unsigned short address,
               const char *data, int len);
    void write(Modbus::FunctionCode code, unsigned short address,
               const QByteArray &data);

signals:
    void dataReached(const QByteArray &data);

private slots:
    void onDataReached(void);

private:
    SerialPortCtrl *m_serial;
    QString m_port;
    unsigned char m_address;
};

#endif // MODBUS_H
