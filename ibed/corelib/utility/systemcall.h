#ifndef SYSTEMCALL_H
#define SYSTEMCALL_H

#include "utility_global.h"

class UTILITYSHARED_EXPORT SystemCall
{
public:
    static SystemCall &instance(void);

public:
    int cmd(const QString &cmd, QString &outinfo);
    int cmd(const QString &cmd);

public:
    SystemCall();
};

#endif // SYSTEMCALL_H
