#include "basedatahandler.h"

BaseDataHandler::BaseDataHandler(quint8 id) :
    IDataHandler(),
    m_msgId(id)
{

}

quint8 BaseDataHandler::msgId() const
{
    return m_msgId;
}

void BaseDataHandler::handle(quint8 id, const NetProtocol::ContentList &list)
{
    Q_UNUSED(id)
    Q_UNUSED(list)
}
