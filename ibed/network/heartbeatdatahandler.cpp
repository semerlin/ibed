#include "heartbeatdatahandler.h"

HeartBeatDataHandler::HeartBeatDataHandler(quint8 id) :
    BaseDataHandler(id)
{

}

void HeartBeatDataHandler::handle(quint8 id, const NetProtocol::ContentList &list)
{
    Q_UNUSED(list)

    //check id
    if(id == msgId())
    {
        //only return 14 bytes data?
        emit heartbeat();
//        if(!list.isEmpty())
//        {
//            if(list.at(0).id == 0x64)
//            {
//                if(list.at(0).data.at(0) == 0)
//                {
//                    emit heartbeat();
//                }
//            }
//        }
    }
}
