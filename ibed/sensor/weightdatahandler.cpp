#include "weightdatahandler.h"
#include <QDebug>

WeightDataHandler::WeightDataHandler(quint8 code, quint16 address) :
    BaseDataHandler(code, address),
    m_weight(0)
{

}

void WeightDataHandler::handle(quint8 code, quint16 address, const QByteArray &data)
{
//    qDebug() << "get weight data";
    //check code
    if(code == fucCode())
    {
        //check register address
        if(address == regAddress())
        {
            //get weight
            if(data.count() >= 2)
            {
                quint16 value = (data.at(3) & 0xff);
                value <<= 8;
                value += (data.at(4) & 0xff);

//                qDebug() << "get weight data: " << value;

                emit weightChanged(value);

//                double weight = value;
//                if(weight != m_weight)
//                {
//                    m_weight = weight;
//                    emit weightChanged(m_weight);
//                }
            }
        }
    }
}
