#ifndef CALLOUTLOCALTERMINATESTATE_H
#define CALLOUTLOCALTERMINATESTATE_H

#include <QFinalState>

class CallOutLocalTerminateState : public QFinalState
{
    Q_OBJECT
public:
    CallOutLocalTerminateState(QState *parent = 0);

signals:
    void terminate();

protected:
    void onEntry(QEvent *event);
};

#endif // CALLOUTTERMINATESTATE_H
