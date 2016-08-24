#ifndef CALLIN_H
#define CALLIN_H

#include <QStateMachine>

class CallInConnectingState;
class CallInConnectedState;
class CallInLocalTerminateState;
class CallInRemoteTerminateState;
class QState;

class CallIn : public QStateMachine
{
public:
    CallIn();

private:
    CallInConnectingState *m_connecting;
    CallInConnectedState *m_connected;
    CallInLocalTerminateState *m_localTerminate;
    CallInRemoteTerminateState *m_remoteTerminate;
    QState *m_running;
};

#endif // CALLIN_H
