#ifndef CALLINCONNECTEDSTATE_H
#define CALLINCONNECTEDSTATE_H


#include <QState>

class CallInConnectedState : public QState
{
public:
    CallInConnectedState(QState *parent = 0);

protected:
    void onEntry(QEvent *event);
    void onExit(QEvent *event);
};

#endif // CALLINCONNECTEDSTATE_H
