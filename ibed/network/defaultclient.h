#ifndef DEFAULTCLIENT_H
#define DEFAULTCLIENT_H

#include "network_global.h"
#include <QMap>
#include <QObject>
#include "netprotocol.h"

class QTcpSocket;
class IDataHandler;
class QMutex;
class QTimer;

class NETWORKSHARED_EXPORT DefaultClient : public QObject
{
    Q_OBJECT

public:
    DefaultClient();
    ~DefaultClient();

public:
    void connectServer(const QString &ip, quint16 port);
    void addHandler(IDataHandler *handler);
    bool isRegistered(void) const;
    void getAdvise(void);
    void getBaseInfo(void);
    void uploadInOut(const QStringList &data);

private slots:
    void onConnectTimeout(void);
    void onConnected(void);
    void onDisconnected(void);
    void onReadReady(void);
    void onRegisterTimeout(void);
    void onRegistered(void);
    void onHeartbeat(void);
    void onHeartOk(void);

signals:
    void connected(void);
    void disconnected(void);
    void connectTimeout(void);
    void registerTimeout(void);
    void registered(void);
    void dataReached(quint8 id, const NetProtocol::ContentList &data);
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
    void adviseUpdate(const QString &data);

private:
    void clear(void);

private:
    QTcpSocket *m_socket;
    QByteArray m_data;
    QMutex *m_mutex;
    NetProtocol *m_protocol;
    QMap<quint8, IDataHandler *> m_handlers;
    bool m_isRegistered;
    QTimer *m_heartTimer;
    int m_heartCnt;
};

#endif // MAINCLIENT_H
