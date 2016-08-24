#include "weightdatahandler.h"

WeightDataHandler::WeightDataHandler(quint8 code, quint16 address) :
    BaseDataHandler(code, address),
    m_weight(0)
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
                quint16 value = data.at(0);
                value <<= 8;
                value += data.at(1);

                double weight = value;
                if(weight != m_weight)
                {
                    m_weight = weight;
                    emit weightChanged(m_weight);
                }
            }
        }
    }
}
