#ifndef MAINMODULE_H
#define MAINMODULE_H

#include "mainmodule_global.h"

class MainWidget;
class StandbyWidget;
class CallDialog;
class ProgressDialog;

class MAINMODULESHARED_EXPORT MainModule
{
public:
    MainModule();

public:
    bool initialize(void);

private:
    MainWidget *m_mainWidget;
    StandbyWidget *m_standbyWidget;
    CallDialog *m_callDialog;
    ProgressDialog *m_progressDialog;
};

#endif // MAINMODULE_H
