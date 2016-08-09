#ifndef IDATAHANDLER_H
#define IDATAHANDLER_H

#include "network_global.h"
#include "netprotocol.h"
#include <QObject>

class NETWORKSHARED_EXPORT IDataHandler : public QObject
{
public:
    IDataHandler() {}
    virtual ~IDataHandler() {}

public:
    virtual quint8 msgId(void) const = 0;
    virtual void handle(quint8 id, const NetProtocol::ContentList &list) = 0;
};

#endif // IHANDLEDATA_H
