#include "weightdatahandler.h"
#include <QDebug>

WeightDataHandler::WeightDataHandler(quint8 code, quint16 address) :
    BaseDataHandler(code, address),
    m_weight(0),
    m_isFirstTime(true),
    m_zeroPoint(0)
{

}

void WeightDataHandler::handle(quint8 code, quint16 address, const QByteArray &data)
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
                quint16 value = (data.at(3) & 0xff);
                value <<= 8;
                value += (data.at(4) & 0xff);

//                qDebug() << "get weight data: " << QString::number(data.at(3), 16)
//                         << "  " << QString::number(data.at(4), 16);


                if(m_isFirstTime)
                {
                    m_isFirstTime = false;
                    m_zeroPoint = value;
                }

                if(value <= m_zeroPoint)
                    value = 0;
                else
                    value -= m_zeroPoint;

                if(value != m_weight)
                {
                    m_weight = value;
                    m_weight /= 100;
                    m_weight *= 2.4;
                    emit weightChanged(m_weight);
                }
            }
        }
    }
}
