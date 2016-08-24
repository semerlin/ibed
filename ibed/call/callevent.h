#ifndef CALLEVENT_H
#define CALLEVENT_H

#include <QEvent>
#include "calldef.h"

class CallEvent : public QEvent
{
public:
    CallEvent(Call::CallStep step) :
        QEvent(QEvent::Type(QEvent::User + 1)),
        m_step(step) {}

    Call::CallStep m_step;
};

#endif // CALLEVENT_H
