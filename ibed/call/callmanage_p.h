#ifndef CALLMANAGE_P_H
#define CALLMANAGE_P_H

#include "call_global.h"
#include <QObject>
#include "call.h"

class Sip;
class CallBtn;
class CallManage;

class CALLSHARED_EXPORT CallManagePrivate : public QObject
{
    Q_OBJECT
public:
    explicit CallManagePrivate(CallManage *parent);
    ~CallManagePrivate();

public:
    Sip *m_sip;
    bool m_isIdle;
    CallBtn *m_btn;
    bool m_isInited;

public:
    void initSip(void);

private slots:
    void onStateChanged(CallState prev, CallState current);

private:
    CallManage *const q_ptr;
    Q_DECLARE_PUBLIC(CallManage)
};

#endif // CALLMANAGE_P

