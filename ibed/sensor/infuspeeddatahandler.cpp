#include "infuspeeddatahandler.h"


InfuSpeedDataHandler::InfuSpeedDataHandler(quint8 code, quint16 address) :
    BaseDataHandler(code, address),
    m_speed(0)
{

}

void InfuSpeedDataHandler::handle(quint8 code, quint16 address, const QByteArray &data)
{
    //check code
    if(code == fucCode())
    {
        //check register address
        if(address == regAddress())
        {
            //get weight
            if(data.count() >= 2)
            {
                quint16 value = data.at(0);
                value <<= 8;
                value += data.at(1);

                if(value != m_speed)
                {
                    m_speed = value;
                    emit speedChanged(m_speed);
                }
            }
        }
    }
}
