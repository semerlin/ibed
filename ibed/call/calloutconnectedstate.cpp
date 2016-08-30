#include "calloutconnectedstate.h"
#include <QDebug>

CallOutConnectedState::CallOutConnectedState(QState *parent) :
    QState(parent)
{

}



void CallOutConnectedState::onEntry(QEvent *event)
{
    Q_UNUSED(event)
    //prepare record

    //prepare udp

    emit connected();
    qDebug() << "enter call out connected state";
}

void CallOutConnectedState::onExit(QEvent *event)
{
    Q_UNUSED(event)
    //stop record

    //diconnect udp
    qDebug() << "exit call out connected state";
}
