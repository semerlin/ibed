#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include "sensor_global.h"
#include <QByteArray>

class SENSORSHARED_EXPORT I2CDevice
{
public:
    static I2CDevice &instance(void);

public:
    void open(void);
    void close(void);
    bool isOpend(void) const;
    void setAddress(unsigned char address);
    int write(const QByteArray &data);
    int write(const char *data, int len);
    int	read(char * data, qint64 maxSize);
    QByteArray read(qint64 maxSize);

private:
    I2CDevice();
    ~I2CDevice();
    int m_fd;
    bool m_isOpened;
};

#endif // I2CDEVICE_H
