#ifndef CALLOUTCONNECTEDSTATE_H
#define CALLOUTCONNECTEDSTATE_H

#include <QState>

class CallOutConnectedState : public QState
{
    Q_OBJECT
public:
    CallOutConnectedState(QState *parent = 0);

signals:
    void connected();

protected:
    void onEntry(QEvent *event);
    void onExit(QEvent *event);
};

#endif // CALLOUTCONNECTEDSTATE_H
