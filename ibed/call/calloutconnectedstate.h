#ifndef CALLOUTCONNECTEDSTATE_H
#define CALLOUTCONNECTEDSTATE_H

#include <QState>

class CallOutConnectedState : public QState
{
public:
    CallOutConnectedState(QState *parent = 0);

protected:
    void onEntry(QEvent *event);
    void onExit(QEvent *event);
};

#endif // CALLOUTCONNECTEDSTATE_H
