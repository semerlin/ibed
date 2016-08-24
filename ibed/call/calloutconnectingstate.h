#ifndef CALLOUTCONNECTINGSTATE_H
#define CALLOUTCONNECTINGSTATE_H

#include <QState>

class CallOutConnectingState : public QState
{
public:
    CallOutConnectingState(QState *parent = 0);

protected:
    void onEntry(QEvent *event);
    void onExit(QEvent *event);
};

#endif // CALLOUTCONNECTINGSTATE_H
