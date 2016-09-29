#ifndef PCF8574_H
#define PCF8574_H

#include <QByteArray>
#include <QString>

class PCF8574
{
public:
    /**
     * @brief PCF8574 construct
     * @param port: i2c port name
     * @param address: pcf8574 address
     */
    explicit PCF8574(const QString &port, quint8 address);
    ~PCF8574();

public:
    /**
     * @brief open pcf8574
     * @return
     */
    bool open(void);

    /**
     * @brief close pcf8574
     */
    void close(void);

    /**
     * @brief set pcf8574 port
     * @param port
     */
    void setPort(const QString &port);

    /**
     * @brief set pcf8574 address
     * @param address
     */
    int setAddress(quint8 address);

    /**
     * @brief write data
     * @param data
     * @return
     */
    quint64 write(const QByteArray &data);
    quint64 write(const char *data, quint64 maxSize);
    QByteArray read(quint64 maxSize);
    qint64 read(char *data, qint64 maxSize);

private:
    int m_fd;
    QString m_port;
    quint8 m_address;
};

#endif // PCF8574_H
