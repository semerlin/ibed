#include "callinconnectedstate.h"
#include <QDebug>

CallInConnectedState::CallInConnectedState(QState *parent) :
    QState(parent)
{

}



void CallInConnectedState::onEntry(QEvent *event)
{
    Q_UNUSED(event)
    //prepare record

    //prepare udp
    qDebug() << "enter call in connected state";
}

void CallInConnectedState::onExit(QEvent *event)
{
    Q_UNUSED(event)
    //stop record

    //diconnect udp
    qDebug() << "exit call in connected state";
}
