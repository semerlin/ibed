#include "callinlocalterminatestate.h"
#include <QDebug>

CallInLocalTerminateState::CallInLocalTerminateState(QState *parent) :
    QFinalState(parent)
{

}

void CallInLocalTerminateState::onEntry(QEvent *event)
{
    Q_UNUSED(event)

    //send message to server

    qDebug() << "enter call in local terminate state";
}
