#ifndef CALLMODULE_H
#define CALLMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"

class CallMange;

class CallModule : public BaseAppModule
{
    Q_OBJECT
public:
    CallModule(const QString &name);
    ~CallModule();

public:
    bool load(const QVariant &val);
    void unload();

signals:
    void callOutConnecting(void);
    void callOutConnected(void);
    void callOutLocalTerminate(void);
    void callOutRemoteTerminate(void);

private:
    CallMange *m_callMange;
};

#endif // CALLMODULE_H
