#include "calloutlocalterminatestate.h"
#include <QDebug>

CallOutLocalTerminateState::CallOutLocalTerminateState(QState *parent) :
    QFinalState(parent)
{

}

void CallOutLocalTerminateState::onEntry(QEvent *event)
{
    Q_UNUSED(event)

    //send message to server

    qDebug() << "enter call out local terminate state";
}
