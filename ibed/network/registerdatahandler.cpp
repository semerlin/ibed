#include "registerdatahandler.h"
#include <QDebug>

RegisterDataHandler::RegisterDataHandler(quint8 id) :
    BaseDataHandler(id)
{
}

void RegisterDataHandler::handle(quint8 id, const NetProtocol::ContentList &list)
{
    //check id
    if(id == msgId())
    {
        if(!list.isEmpty())
        {
            if(list.at(0).id == 0xc8)
            {
                if(list.at(0).data.at(0) == 0)
                {
                    emit registered();
                }
            }
        }
    }
}
