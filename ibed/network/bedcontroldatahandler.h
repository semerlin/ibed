#ifndef BEDCONTROLDATAHANDLER_H
#define BEDCONTROLDATAHANDLER_H

#include "network_global.h"
#include "basedatahandler.h"
#include <QList>
#include <QPair>

class NETWORKSHARED_EXPORT BedControlDataHandler : public BaseDataHandler
{
    Q_OBJECT

public:
    BedControlDataHandler(quint8 id);
    ~BedControlDataHandler();

public:
    void handle(quint8 id, const NetProtocol::ContentList &list);

signals:
    void motorMove(const QMap<quint8, quint8> &moves);
};



#endif // BEDCONTROLDATAHANDLER_H
