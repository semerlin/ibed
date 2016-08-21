#include "sht20.h"
#include "i2cdevice.h"
#include "applogger.h"

static double sLastTemperValue = 0;
static double sLastHumValue = 0;

// CRC
const unsigned short POLYNOMIAL = 0x131; //P(x)=x^8+x^5+x^4+1 = 100110001

static unsigned char SHT2x_CalCrc(unsigned char data[], unsigned char nbrOfBytes)
{
    unsigned char crc = 0;
    unsigned char byteCtr;
    //calculates 8-Bit checksum with given polynomial
    for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
    {
        crc ^= (data[byteCtr]);

        for(unsigned char bit = 8; bit > 0; --bit)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ POLYNOMIAL;
            else
                crc = (crc << 1);
        }
    }

    return crc;
}

SHT20::SHT20()
{

}

double SHT20::temperature(void)
{
    if(!I2CDevice::instance().isOpend())
        I2CDevice::instance().open();

    I2CDevice::instance().setAddress(0x40);

    char data[4];
    data[0] = 0xe3;
    I2CDevice::instance().write(data, 1);
    I2CDevice::instance().read(data, 3);

    int val = data[0];
    val <<= 8;
    val += data[1];

    if(SHT2x_CalCrc((unsigned char*)data, 2) != data[2])
        return sLastTemperValue;

    sLastTemperValue = -46.85 + 175.72 * val / 65535;
    return sLastTemperValue;
}

double SHT20::humidity(void)
{
    if(!I2CDevice::instance().isOpend())
        I2CDevice::instance().open();

    I2CDevice::instance().setAddress(0x40);

    char data[4];
    data[0] = 0xe5;
    I2CDevice::instance().write(data, 1);
    I2CDevice::instance().read(data, 3);

    int val = data[0];
    val <<= 8;
    val += data[1];

    if(SHT2x_CalCrc((unsigned char*)data, 2) != data[2])
        return sLastHumValue;

    sLastHumValue = -6 + 125 * val / 65535;
    return sLastHumValue;
}

