#ifndef CALLINCONNECTINGSTATE_H
#define CALLINCONNECTINGSTATE_H


#include <QState>

class CallInConnectingState : public QState
{
public:
    CallInConnectingState(QState *parent = 0);

protected:
    void onEntry(QEvent *event);
    void onExit(QEvent *event);
};
#endif // CALLINCONNECTINGSTATE_H
