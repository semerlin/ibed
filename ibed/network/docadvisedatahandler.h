#ifndef DOCADVISEDATAHANDLER_H
#define DOCADVISEDATAHANDLER_H


#include "network_global.h"
#include "basedatahandler.h"

class DocAdviseDataHandler : public BaseDataHandler
{
    Q_OBJECT
public:
    DocAdviseDataHandler(quint8 id);
    ~DocAdviseDataHandler();

public:
    void handle(quint8 id, const NetProtocol::ContentList &list);

signals:
    void adviseChanged(const QString &advise);
};

#endif // DOCADVISEDATAHANDLER_H
