#ifndef CALLOUT_H
#define CALLOUT_H

#include <QStateMachine>

class CallOutConnectingState;
class CallOutConnectedState;
class CallOutLocalTerminateState;
class CallOutRemoteTerminateState;
class QState;

class CallOut : public QStateMachine
{
    Q_OBJECT
public:
    CallOut();

signals:
    void connecting(void);
    void connected(void);
    void localTerminate(void);
    void remoteTerminate(void);

private:
    CallOutConnectingState *m_connecting;
    CallOutConnectedState *m_connected;
    CallOutLocalTerminateState *m_localTerminate;
    CallOutRemoteTerminateState *m_remoteTerminate;
    QState *m_running;
};

#endif // CALLOUT_H
