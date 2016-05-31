#ifndef IAPPLANCHER_H
#define IAPPLANCHER_H

#include "framework_global.h"

/**
 * @brief application lanch framework
 */
class FRAMEWORKSHARED_EXPORT IAppLancher
{
public:
    IAppLancher() {}

public:
    /**
     * @brief run application
     * @param argc
     * @param argv
     * @return
     */
    virtual int run(int argc, char **argv) = 0;

    /**
     * @brief restart application
     * @return
     */
    virtual int restart(void) = 0;
};

#endif // IAPPLANCHER_H
