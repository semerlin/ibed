#include "callinconnectingstate.h"
#include <QDebug>

CallInConnectingState::CallInConnectingState(QState *parent) :
    QState(parent)
{

}

void CallInConnectingState::onEntry(QEvent *event)
{
    Q_UNUSED(event)
    //paly call out sound

    //send message to server

    qDebug() << "enter call in connecting state";
}

void CallInConnectingState::onExit(QEvent *event)
{
    Q_UNUSED(event)
    //stop call out sound

    qDebug() << "exit call in connecting state";
}
