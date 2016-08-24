#ifndef CALLINLOCALTERMINATESTATE_H
#define CALLINLOCALTERMINATESTATE_H


#include <QFinalState>

class CallInLocalTerminateState : public QFinalState
{
public:
    CallInLocalTerminateState(QState *parent = 0);

protected:
    void onEntry(QEvent *event);
};

#endif // CALLINLOCALTERMINATESTATE_H
