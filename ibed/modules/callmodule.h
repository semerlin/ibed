#ifndef CALLMODULE_H
#define CALLMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"

class CallManage;

class CallModule : public BaseAppModule
{
    Q_OBJECT
public:
    CallModule(const QString &name);
    ~CallModule();

public:
    bool load(const QVariant &val);
    void unload();

public slots:
    void callOutRequest(void);
    void callHangup(void);

signals:
    void callOutConnecting(void);
    void callInConnecting(void);
    void callConnected(void);
    void callTerminate(void);

private:
    CallManage *m_callMange;
};

#endif // CALLMODULE_H
