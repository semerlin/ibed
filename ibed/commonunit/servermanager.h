#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "commonunit_global.h"
#include <QHash>


class COMMONUNITSHARED_EXPORT ServerManager : public QObject
{
    Q_OBJECT

public:
    typedef enum
    {
        Default,
        Sip,
        Count,
    }ServerType;

public:
    static ServerManager &instance(void);

public:
    /**
     * @brief get specified server address
     * @param type - server type
     * @return server ip address
     */
    QString address(const ServerType &type) const;

    /**
     * @brief get specified server port
     * @param type - server type
     * @return server port
     */
    quint16 port(const ServerType &type) const;

public slots:
    /**
     * @brief set specified server ip address
     * @param type - server type
     * @param address - server address
     */
    void setAddress(const ServerType &type, const QString &address);

    /**
     * @brief set specified server port
     * @param type - server type
     * @param port - server port
     */
    void setPort(const ServerType &type, quint16 port);

    /**
     * @brief save server information to ini file
     */
    void save(void);

signals:
    void addressChanged(const ServerType &type, const QString &address);
    void portChanged(const ServerType &type, quint16 port);

private:
    ServerManager();
    void load(void);

private:
    QHash<ServerType, QString> m_addresses;
    QHash<ServerType, quint16> m_ports;
};

#endif // SERVERMANGER_H
