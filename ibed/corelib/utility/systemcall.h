#ifndef SYSTEMCALL_H
#define SYSTEMCALL_H

#include "utility_global.h"

class UTILITYSHARED_EXPORT SystemCall
{
public:
    static int getCmdOut(const QString &cmd, QString &outinfo);
    static int system(const QString &cmd);
    static void sync(void);
};

#endif // SYSTEMCALL_H
