#include "bedcontroldatahandler.h"
#include <QMap>

BedControlDataHandler::BedControlDataHandler(quint8 id) :
    BaseDataHandler(id)
{

}

BedControlDataHandler::~BedControlDataHandler()
{

}

void BedControlDataHandler::handle(quint8 id, const NetProtocol::ContentList &list)
{
    //check id
    if(id == msgId())
    {
        if(!list.isEmpty())
        {
            QMap<quint8, quint8> moves;
            if(list.count() >= 2)
            {
                for(int i = 0; i < list.count() / 2; ++i)
                {
                    quint8 id = 0;
                    quint8 dir = 0;

                    for(int j = 0; j < 2; j++)
                    {
                        if(list.at(i + j).id == 1510)
                            id = list.at(i + j).data.at(0);
                        else if(list.at(i +j).id == 1511)
                            dir = list.at(i +j).data.at(0);
                    }

                    moves.insert(id, dir);
                }
            }

            emit motorMove(moves);
        }
    }
}
