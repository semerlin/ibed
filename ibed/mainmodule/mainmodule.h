#ifndef MAINMODULE_H
#define MAINMODULE_H

#include "mainmodule_global.h"

class ModuleManger;

class MAINMODULESHARED_EXPORT MainModule
{
public:
    MainModule();

public:
    bool initialize(void);
    ModuleManger *manger(void) const;

private:
    ModuleManger *m_manger;
};

#endif // MAINMODULE_H
