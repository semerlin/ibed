#ifndef APPSETTING_P_H
#define APPSETTING_P_H

#include "commonunit_global.h"
#include <QHash>

class COMMONUNITSHARED_EXPORT AppSettingPrivate
{
public:
    void setDefault();
    QHash<QString, QVariant> m_params;

};

#endif // APPSETTING_P

