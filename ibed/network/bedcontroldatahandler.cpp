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
            foreach(const NetProtocol::Content &content, list)
            {
                quint8 id = 0;
                quint8 dir = 0;
                switch(content.id)
                {
                //motor id
                case 1510:
                    id = content.data.at(0);
                    break;
                //motor direction
                case 1511:
                    dir = content.data.at(0);
                    break;
                default:
                    break;
                }

                moves.insert(id, dir);
            }

            emit motorMove(moves);
        }
    }
}
