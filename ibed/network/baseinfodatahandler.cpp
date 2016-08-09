#include "baseinfodatahandler.h"


BaseinfoDataHandler::BaseinfoDataHandler(quint8 id) :
    BaseDataHandler(id)
{

}

BaseinfoDataHandler::~BaseinfoDataHandler()
{

}

void BaseinfoDataHandler::handle(quint8 id, const NetProtocol::ContentList &list)
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
                case 8000:
                    break;
                case 8011:
                    emit nameChanged(content.data);
                    break;
                case 8012:
                    emit sexChanged(content.data);
                    break;
                case 8013:
                    emit ageChanged(content.data);
                    break;
                case 8014:
                    emit doctorChanged(content.data);
                    break;
                case 8015:
                    emit nurseChanged(content.data);
                    break;
                case 8016:
                    emit timeChanged(content.data);
                    break;
                case 8017:
                    emit eatChanged(content.data);
                    break;
                case 8018:
                    emit allergyChanged(content.data);
                    break;
                case 8021:
                    emit levelChanged(content.data);
                    break;
                case 8022:
                    emit bedChanged(content.data);
                    break;
                default:
                    break;
                }
            }
        }
    }
}
