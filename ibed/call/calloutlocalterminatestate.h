#ifndef CALLOUTLOCALTERMINATESTATE_H
#define CALLOUTLOCALTERMINATESTATE_H

#include <QFinalState>

class CallOutLocalTerminateState : public QFinalState
{
public:
    CallOutLocalTerminateState(QState *parent = 0);

protected:
    void onEntry(QEvent *event);
};

#endif // CALLOUTTERMINATESTATE_H
