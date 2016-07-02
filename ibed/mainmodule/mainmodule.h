#ifndef MAINMODULE_H
#define MAINMODULE_H

#include "mainmodule_global.h"

class MainWidget;

class MAINMODULESHARED_EXPORT MainModule
{
public:
    MainModule();

public:
    bool initialize(void);

private:
    MainWidget *m_mainWidget;
};

#endif // MAINMODULE_H
