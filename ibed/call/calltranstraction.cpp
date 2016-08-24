#include "calltranstraction.h"


CallTranstraction::CallTranstraction(Call::CallStep step) :
    m_step(step)
{

}

bool CallTranstraction::eventTest(QEvent *event)
{
    if(event->type() != QEvent::Type(QEvent::User+1))
        return false;

    CallEvent *ce = static_cast<CallEvent*>(event);
    return (m_step == ce->m_step);
}

void CallTranstraction::onTransition(QEvent *event)
{
    Q_UNUSED(event)
}
