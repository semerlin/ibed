#ifndef BASEAPPLANCHER_H
#define BASEAPPLANCHER_H

#include "framework_global.h"
#include "iapplancher.h"


/**
 * @brief base application lanch framework
 */
class FRAMEWORKSHARED_EXPORT BaseAppLancher : public IAppLancher
{
public:
    BaseAppLancher();

public:
    virtual int run(int argc, char **argv);
//    virtual void addStep(stepFunc func);
};

#endif // BASEAPPLANCHER_H
