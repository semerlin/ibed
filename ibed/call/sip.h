#ifndef SIP_H
#define SIP_H

#include "call.h"
#include <QObject>
#include "pjsua.h"
#include "call.h"

class QTimer;

class Sip : public QObject
{
    Q_OBJECT
public:
    Sip();
    virtual ~Sip();

public:
    bool init(void);
//    int reg(const QString &name, const QString &passwd, const QString &domain);
    bool reg(const QString &name, const char *passwd, const QString &domain);
    int dial(const QString &num);
    void answer();
    void hangup(void);
    void destroy();
    void reset(void);

signals:
    void stateChanged(CallState prev, CallState current);

private:
    static void onIncomingCall(pjsua_acc_id acc_id, pjsua_call_id call_id,pjsip_rx_data *rdata);
    static void onCallState(pjsua_call_id call_id, pjsip_event *e);
    static void onCallMediaState(pjsua_call_id call_id);

private slots:
    void onTimeOut(void);

private:
    pjsua_acc_id m_id;
    QString m_domain;
    bool m_isRegistered;
    QTimer *m_timer;
    static CallState m_prevState;
    static CallState m_curState;
    static pjsua_call_id m_callId;
    CallState m_prev;
    CallState m_cur;
};



#endif // SIP_H
