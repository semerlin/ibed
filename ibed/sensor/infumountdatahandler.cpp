#include "infumountdatahandler.h"


InfuMountDataHandler::InfuMountDataHandler(quint8 code, quint16 address) :
    BaseDataHandler(code, address),
    m_mount(0)
{

}

void InfuMountDataHandler::handle(quint8 code, quint16 address, const QByteArray &data)
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

                if(value != m_mount)
                {
                    m_mount = value;
                    emit mountChanged(m_mount);
                }
            }
        }
    }
}
