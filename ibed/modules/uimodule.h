#ifndef UIMODULE_H
#define UIMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"


class MainWidget;
class StandbyWidget;
class CallDialog;
class ProgressDialog;

class MODULESSHARED_EXPORT UiModule : public BaseAppModule
{
public:
    UiModule(const QString &name);
    ~UiModule();

public:
    bool load(const QVariant &val);
    void unload();

public:
    MainWidget *mainWidget(void) const;

private:
    MainWidget *m_mainWidget;
    StandbyWidget *m_standbyWidget;
    CallDialog *m_callDialog;
    ProgressDialog *m_progressDialog;
};

#endif // UIMODULE_H
