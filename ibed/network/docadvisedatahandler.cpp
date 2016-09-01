#include "docadvisedatahandler.h"


DocAdviseDataHandler::DocAdviseDataHandler(quint8 id) :
    BaseDataHandler(id)
{

}

DocAdviseDataHandler::~DocAdviseDataHandler()
{

}

void DocAdviseDataHandler::handle(quint8 id, const NetProtocol::ContentList &list)
{
    //check id
    if(id == msgId())
    {
        if(!list.isEmpty())
        {
            foreach(const NetProtocol::Content &content, list)
            {
                switch(content.id)
                {
                case 8100:
                    break;
                case 8110:
                    emit adviseChanged(content.data);
                    break;
                default:
                    break;
                }
            }
        }
    }
}
