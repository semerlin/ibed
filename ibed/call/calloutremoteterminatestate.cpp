#include "calloutremoteterminatestate.h"
#include <QDebug>

CallOutRemoteTerminateState::CallOutRemoteTerminateState(QState *parent) :
    QFinalState(parent)
{

}

void CallOutRemoteTerminateState::onEntry(QEvent *event)
{
    Q_UNUSED(event)

    //send message to server

    emit terminate();

    qDebug() << "enter call out remote terminate state";
}

