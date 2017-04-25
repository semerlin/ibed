#ifndef IAPPLAUNCH_H
#define IAPPLAUNCH_H

#include "framework_global.h"

/**
 * @brief application launch framework
 */
class FRAMEWORKSHARED_EXPORT IAppLaunch
{
public:
    IAppLaunch() {}

public:
    /**
     * @brief run application
     * @param argc
     * @param argv
     * @return
     */
    virtual int run(int argc, char **argv) = 0;
};

#endif // IAPPLANCHER_H
