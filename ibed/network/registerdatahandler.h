#ifndef REGISTERDATAHANDLER_H
#define REGISTERDATAHANDLER_H

#include "network_global.h"
#include "basedatahandler.h"

class NETWORKSHARED_EXPORT RegisterDataHandler : public BaseDataHandler
{
    Q_OBJECT

public:
    RegisterDataHandler(quint8 id);
    ~RegisterDataHandler() {}

public:
    void handle(quint8 id, const NetProtocol::ContentList &list);

signals:
    void registered(void);
};

#endif // REGISTERDATAHANDLER_H
