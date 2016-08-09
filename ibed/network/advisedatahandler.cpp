#include "advisedatahandler.h"


AdviseDataHandler::AdviseDataHandler(quint8 id) :
    BaseDataHandler(id)
{

}

AdviseDataHandler::~AdviseDataHandler()
{

}

void AdviseDataHandler::handle(quint8 id, const NetProtocol::ContentList &list)
{
    //check id
    if(id == msgId())
    {
        if(!list.isEmpty())
        {
            foreach(const NetProtocol::Content &content, list)
            {
                emit adviseUpdate(content.data);
            }
        }
    }
}
