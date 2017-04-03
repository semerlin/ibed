#ifndef NETCONFIG_H
#define NETCONFIG_H

#include "commonunit_global.h"
#include "funcwrap.h"
#include <QString>

class COMMONUNITSHARED_EXPORT NetConfig
{

public:
    static NetConfig &instance();

public:
    /**
     * @brief get device ip address
     * @return ip address
     */
    GETTER(address, QString);

    /**
     * @brief get device netmask
     * @return device netmask
     */
    GETTER(netmask, QString);

    /**
     * @brief get deive gateway
     * @return device gateway
     */
    GETTER(gateway, QString);

    /**
     * @brief get devide network name
     * @return device network name
     */
    GETTER(name, QString);

public:
    /**
     * @brief set device ip address
     * @param ip - ip address
     */
    void setAddress(const QString &ip);

    /**
     * @brief set device netmask
     * @param netmask - device netmask
     */
    void setNetmask(const QString &netmask);

    /**
     * @brief set device gateway
     * @param gateway - device gateway
     */
    void setGateway(const QString &gateway);

    /**
     * @brief set device network name
     * @param name - device network name
     */
    void setName(const QString &name);

    /**
     * @brief save device network information to ini file
     */
    void save();

private:
    NetConfig();
    void load();

private:
    QString m_address;
    QString m_netmask;
    QString m_gateway;
    QString m_name;
};

#endif // NETCONFIG_H
