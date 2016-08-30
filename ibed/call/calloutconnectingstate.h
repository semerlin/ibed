#ifndef CALLOUTCONNECTINGSTATE_H
#define CALLOUTCONNECTINGSTATE_H

#include <QState>

class CallOutConnectingState : public QState
{
    Q_OBJECT
public:
    CallOutConnectingState(QState *parent = 0);

signals:
    void connecting();

protected:
    void onEntry(QEvent *event);
    void onExit(QEvent *event);
};

#endif // CALLOUTCONNECTINGSTATE_H
