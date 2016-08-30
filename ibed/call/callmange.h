#ifndef CALLMANGE_H
#define CALLMANGE_H

#include <QObject>

class CallBtn;
class CallOut;
class CallIn;
class QStateMachine;

class CallMange : public QObject
{
    Q_OBJECT

public:
    CallMange();

signals:
    void callOutConnecting(void);
    void callOutConnected(void);
    void callOutLocalTerminate(void);
    void callOutRemoteTerminate(void);

private slots:
    void onCallOutRequest(void);
    void onCallInRequest(void);
    void onConnected(void);
    void onLocalTerminate(void);
    void onRemoteTerminate(void);

private:
    CallBtn *m_btn;
    CallOut *m_callOut;
    CallIn *m_callIn;
    QStateMachine *m_activeMachine;
};

#endif // CALLMANGE_H
