#include "infucountdatahandler.h"


InfuCountDataHandler::InfuCountDataHandler(quint8 code, quint16 address) :
    BaseDataHandler(code, address),
    m_count(0)
{

}

void InfuCountDataHandler::handle(quint8 code, quint16 address, const QByteArray &data)
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

                if(value != m_count)
                {
                    m_count = value;
                    emit countChanged(m_count);
                }
            }
        }
    }
}
