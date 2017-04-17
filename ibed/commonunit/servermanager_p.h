#ifndef SERVERMANAGER_P_H
#define SERVERMANAGER_P_H

#include "commonunit_global.h"
#include "servermanager.h"
#include <QHash>

class COMMONUNITSHARED_EXPORT ServerManagerPrivate
{
public:
    void load(void);

public:
    QHash<ServerManager::ServerType, QString> m_addresses;
    QHash<ServerManager::ServerType, quint16> m_ports;

};

#endif // SERVERMANAGER_P

