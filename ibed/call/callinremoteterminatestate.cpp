#include "callinremoteterminatestate.h"
#include <QDebug>

CallInRemoteTerminateState::CallInRemoteTerminateState(QState *parent) :
    QFinalState(parent)
{

}

void CallInRemoteTerminateState::onEntry(QEvent *event)
{
    Q_UNUSED(event)

    //send message to server

    qDebug() << "enter call in remote terminate state";
}

