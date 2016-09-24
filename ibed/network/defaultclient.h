#ifndef DEFAULTCLIENT_H
#define DEFAULTCLIENT_H

#include "network_global.h"
#include <QMap>
#include <QObject>
#include "netprotocol.h"

class QTcpSocket;
class QTimer;
class DefaultDataProcess;
class QThread;

class NETWORKSHARED_EXPORT DefaultClient : public QObject
{
    Q_OBJECT

public:
    DefaultClient();
    ~DefaultClient();

public:
    void connectServer(const QString &ip, quint16 port);
    bool isRegistered(void) const;
    void getAdvise(void);
    void getBaseInfo(void);
    void uploadInOut(const QStringList &data);
    void sendInfuStatus(int status);
    void sendInfuSpeed(int speed);
    void sendInfuLeft(int left);
    void sendWeight(int weight);
    void setDeviceNum(quint16 device);
    void setLocalInfo(const QString &ip, const QString &netmask, const QString &gateway);

private slots:
    void onConnectTimeout(void);
    void onConnected(void);
    void onDisconnected(void);
    void onReadReady(void);
    void onRegisterTimeout(void);
    void onRegistered(void);
    void onHeartbeat(void);
    void onHeartOk(void);
    void onReconnect(void);

signals:
    void connected(void);
    void disconnected(void);
    void connectTimeout(void);
    void registerTimeout(void);
    void registered(void);
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
    void motorMove(const QMap<quint8, quint8> &moves);

signals:
    void dataReached(const QByteArray &data);

private:
    void clear(void);
    bool socketWrite(const QByteArray &data);

private:
    QTcpSocket *m_socket;
    bool m_isRegistered;
    QTimer *m_heartTimer;
    int m_heartCnt;
    DefaultDataProcess *m_dataProcess;
    QThread *m_dataThread;
    QString m_ip;
    QString m_netmask;
    QString m_gateway;
};

#endif // MAINCLIENT_H
