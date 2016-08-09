#ifndef BASEINFODATAHANDLER_H
#define BASEINFODATAHANDLER_H

#include "network_global.h"
#include "basedatahandler.h"

class BaseinfoDataHandler : public BaseDataHandler
{
    Q_OBJECT
public:
    BaseinfoDataHandler(quint8 id);
    ~BaseinfoDataHandler();

public:
    void handle(quint8 id, const NetProtocol::ContentList &list);

signals:
    void nameChanged(const QString &name);
    void sexChanged(const QString &sex);
    void ageChanged(const QString &age);
    void bedChanged(const QString &bed);
    void levelChanged(const QString &level);
    void timeChanged(const QString &time);
    void doctorChanged(const QString &doctor);
    void eatChanged(const QString &eat);
    void nurseChanged(const QString &nurse);
    void adviseChanged(const QString &advise);
    void allergyChanged(const QString &allergy);
};

#endif // BASEINFODATAHANDLER_H
