#ifndef NETWORKMODULE_H
#define NETWORKMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"
#include <QMap>

class DefaultClient;

class MODULESSHARED_EXPORT NetworkModule : public BaseAppModule
{
    Q_OBJECT

public:
    NetworkModule(const QString &name);
    ~NetworkModule();

public:
    bool load(const QVariant &val);
    void unload();

public:
    void init(void);

public slots:
    void reconnect(const QString &ip, quint16 port, quint16 device);
    void getAdvise(void);
    void uploadInOut(const QStringList &data);
    void sendInfuStatus(int status);
    void sendInfuSpeed(int speed);
    void sendInfuLeft(int left);
    void sendWeight(double weight);

signals:
    void registered();
    void registerTimeout();
    void disconnected();
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

private:
    DefaultClient *m_defaultClient;
};

#endif // NETWORKMODULE_H
