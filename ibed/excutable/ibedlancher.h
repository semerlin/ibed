#ifndef IBEDLANCHER_H
#define IBEDLANCHER_H


#include "baseapplancher.h"
#include "lanchwidget.h"
#include "modulemanger.h"
#include "hardwaremodule.h"
#include "iapplancherwidget.h"

class IBedLancher
{
public:
    static IBedLancher& instance();

    // AppLancherShell interface
public:
    int run(int argc, char **argv);

private:
    IBedLancher();
};

#endif // IBEDLANCHER_H
