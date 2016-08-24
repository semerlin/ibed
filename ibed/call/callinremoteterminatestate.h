#ifndef CALLINREMOTETERMINATESTATE_H
#define CALLINREMOTETERMINATESTATE_H


#include <QFinalState>

class CallInRemoteTerminateState : public QFinalState
{
public:
    CallInRemoteTerminateState(QState *parent = 0);

protected:
    void onEntry(QEvent *event);
};

#endif // CALLINREMOTETERMINATESTATE_H
