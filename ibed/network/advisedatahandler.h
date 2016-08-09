#ifndef ADVISEDATAHANDLER_H
#define ADVISEDATAHANDLER_H

#include "network_global.h"
#include "basedatahandler.h"


class NETWORKSHARED_EXPORT AdviseDataHandler : public BaseDataHandler
{
    Q_OBJECT

public:
    AdviseDataHandler(quint8 id);
    ~AdviseDataHandler();

public:
    void handle(quint8 id, const NetProtocol::ContentList &list);

signals:
    void adviseUpdate(const QString &data);
};

#endif // ADVISEDATAHANDLER_H
