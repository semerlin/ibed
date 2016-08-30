#ifndef DEFAULTDATAPROCESS_H
#define DEFAULTDATAPROCESS_H

#include "network_global.h"
#include <QObject>
#include <QMap>
#include "netprotocol.h"

class QMutex;
class IDataHandler;

class NETWORKSHARED_EXPORT DefaultDataProcess : public QObject
{
    Q_OBJECT
public:
    DefaultDataProcess();
    ~DefaultDataProcess();

public slots:
    void onProcessData(const QByteArray &newData);

public:
    void addHandler(IDataHandler *handler);
    void reset(void);
    QByteArray package(quint8 id, const NetProtocol::ContentList &contents = NetProtocol::ContentList());

signals:
    void registered(void);
    void heartbeat(void);
    void nameChanged(const QString& name);
    void sexChanged(const QString& sex);
    void ageChanged(const QString& age);
    void bedChanged(const QString& bed);
    void levelChanged(const QString& level);
    void timeChanged(const QString& time);
    void doctorChanged(const QString& doctor);
    void eatChanged(const QString& eat);
    void nurseChanged(const QString& burse);
    void adviseChanged(const QString& advise);
    void allergyChanged(const QString& allergy);
    void adviseUpdate(const QString& advise);

private:
    QMutex *m_mutex;
    QByteArray m_data;
    NetProtocol *m_protocol;
    QMap<quint8, IDataHandler *> m_handlers;
};

#endif // DEFAULTDATAPROCESS_H
