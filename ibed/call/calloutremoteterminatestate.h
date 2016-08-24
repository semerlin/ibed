#ifndef CALLOUTREMOTETERMINATESTATE_H
#define CALLOUTREMOTETERMINATESTATE_H

#include <QFinalState>

class CallOutRemoteTerminateState : public QFinalState
{
public:
    CallOutRemoteTerminateState(QState *parent = 0);

protected:
    void onEntry(QEvent *event);
};

#endif // CALLOUTREMOTETERMINATESTATE_H
