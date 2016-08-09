#ifndef BASEDATAHANDLER_H
#define BASEDATAHANDLER_H

#include "network_global.h"
#include "idatahandler.h"

class NETWORKSHARED_EXPORT BaseDataHandler : public IDataHandler
{
public:
    explicit BaseDataHandler(quint8 id);
    virtual ~BaseDataHandler() {}

public:
    quint8 msgId() const;
    virtual void handle(quint8 id, const NetProtocol::ContentList &list);

private:
    quint8 m_msgId;
};


#endif // BASEDATAHANDLER_H
