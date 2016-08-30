#include "calloutconnectingstate.h"
#include <QDebug>

CallOutConnectingState::CallOutConnectingState(QState *parent) :
    QState(parent)
{

}

void CallOutConnectingState::onEntry(QEvent *event)
{
    Q_UNUSED(event)
    //paly call out sound

    //send message to server

    emit connecting();
    qDebug() << "enter call out connecting state";
}

void CallOutConnectingState::onExit(QEvent *event)
{
    Q_UNUSED(event)
    //stop call out sound

    qDebug() << "exit call out connecting state";
}

