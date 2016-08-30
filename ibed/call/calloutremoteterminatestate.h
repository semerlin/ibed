#ifndef CALLOUTREMOTETERMINATESTATE_H
#define CALLOUTREMOTETERMINATESTATE_H

#include <QFinalState>

class CallOutRemoteTerminateState : public QFinalState
{
    Q_OBJECT
public:
    CallOutRemoteTerminateState(QState *parent = 0);

signals:
    void terminate();

protected:
    void onEntry(QEvent *event);
};

#endif // CALLOUTREMOTETERMINATESTATE_H
