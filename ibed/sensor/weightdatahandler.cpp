#include "weightdatahandler.h"

WeightDataHandler::WeightDataHandler(quint8 code, quint16 address) :
    BaseDataHandler(code, address)
{

}

void WeightDataHandler::handle(quint8 code, quint16 address, const QByteArray &data)
{
    //check id
//    if(id == msgAddress())
//    {

//    }
}
