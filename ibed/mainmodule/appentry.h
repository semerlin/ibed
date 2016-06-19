#ifndef APPENTRY_H
#define APPENTRY_H

#include "mainmodule_global.h"

class MAINMODULESHARED_EXPORT AppEntry
{
public:
    static AppEntry &instance();

public:
    int run(int argc, char **argv);

private:
    AppEntry();
};

#endif // APPENTRY_H
