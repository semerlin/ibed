#include "infucountdatahandler.h"
#include <QDebug>


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
            //get count
            if(data.count() >= 2)
            {
                quint16 value = (data.at(3) & 0xff);
                value <<= 8;
                value += (data.at(4) & 0xff);

//                qDebug() << "get infu count: " << value;

                emit countChanged(value);


//                if(value != m_count)
//                {
//                    m_count = value;
//                    emit countChanged(m_count);
//                }
            }
        }
    }
}
