#ifndef HEARTBEATDATAHANDLER_H
#define HEARTBEATDATAHANDLER_H

#include "network_global.h"
#include "basedatahandler.h"

class NETWORKSHARED_EXPORT HeartBeatDataHandler : public BaseDataHandler
{
    Q_OBJECT

public:
    HeartBeatDataHandler(quint8 id);

public:
    void handle(quint8 id, const NetProtocol::ContentList &list);

signals:
    void heartbeat();
};

#endif // HEARTRATEDATAHANDLER_H
