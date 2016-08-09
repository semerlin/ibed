#ifndef SERVERMANGER_H
#define SERVERMANGER_H

#include "commonunit_global.h"
#include <QHash>


class COMMONUNITSHARED_EXPORT ServerManger : public QObject
{
    Q_OBJECT

public:
    typedef enum
    {
        Default,
        Monitor,
        Count,
    }ServerType;

public:
    static ServerManger &instance(void);

public:
    QString address(const ServerType &type) const;
    quint16 port(const ServerType &type) const;

public slots:
    void setAddress(const ServerType &type, const QString &address);
    void setPort(const ServerType &type, quint16 port);
    void save(void);
    void load(void);

signals:
    void addressChanged(const ServerType &type, const QString &address);
    void portChanged(const ServerType &type, quint16 port);

private:
    ServerManger();
    void createDefault(void);

private:
    QHash<ServerType, QString> m_addresses;
    QHash<ServerType, quint16> m_ports;
};

#endif // SERVERMANGER_H
