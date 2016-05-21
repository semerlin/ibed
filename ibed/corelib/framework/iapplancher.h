#ifndef IAPPLANCHER_H
#define IAPPLANCHER_H

#include "framework_global.h"
#include <QVariant>

/**
 * @brief application lanch framework
 */
class FRAMEWORKSHARED_EXPORT IAppLancher
{
public:
    typedef bool (*Func)(QVariant param);
    IAppLancher();

public:
    virtual int run(int argc, char **argv) = 0;
    virtual QString &error(void) const;

public:
    virtual void addStep(Func func);
    virtual void setStep(QList<Func> funcs) = 0;
};

#endif // IAPPLANCHER_H
