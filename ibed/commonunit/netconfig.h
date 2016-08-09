#ifndef NETCONFIG_H
#define NETCONFIG_H

#include "commonunit_global.h"
#include <QString>

class COMMONUNITSHARED_EXPORT NetConfig
{

public:
    static NetConfig &instance();

public:
    QString address(void) const;
    QString netmask(void) const;
    QString gateway(void) const;
    QString name(void) const;

public:
    void setAddress(const QString &ip);
    void setNetmask(const QString &netmask);
    void setGateway(const QString &gateway);
    void setName(const QString &name);
    void save();
    void load();

private:
    NetConfig();
    void createDefault(void);

private:
    QString m_address;
    QString m_netmask;
    QString m_gateway;
    QString m_name;
};

#endif // NETCONFIG_H
