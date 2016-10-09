#ifndef CALLMANGE_H
#define CALLMANGE_H

#include <QObject>
#include "call.h"

class Sip;
class CallBtn;

class CallMange : public QObject
{
    Q_OBJECT

public:
    CallMange();

public:
    bool init();

public slots:
    void onCallOutRequest(void);
    void onTerminate(void);
    void onRestart(void);

signals:
    void callOutConnecting(void);
    void callInConnecting(void);
    void callConnected(void);
    void callTerminate(void);

private slots:
    void onStateChanged(CallState prev, CallState current);

private:
    Sip *m_sip;
    bool m_isIdle;
    CallBtn *m_btn;
};

#endif // CALLMANGE_H
