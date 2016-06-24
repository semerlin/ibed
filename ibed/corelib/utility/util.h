#ifndef UTIL_H
#define UTIL_H

#include "utility_global.h"

class UTILITYSHARED_EXPORT Util
{
public:
    static Util& instance(void);
    QString fileName(const QString &name);
    QString fileSuffix(const QString &name);

private:
    Util();
};

#endif // UTIL_H
