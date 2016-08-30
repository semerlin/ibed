#ifndef CALLTRANSTRACTION_H
#define CALLTRANSTRACTION_H

#include "call_global.h"
#include <QAbstractTransition>
#include "callevent.h"

class CALLSHARED_EXPORT CallTranstraction : public QAbstractTransition
{
public:
    CallTranstraction(Call::CallStep step);

protected:
    virtual bool eventTest(QEvent *event);
    virtual void onTransition(QEvent *event);

private:
    Call::CallStep m_step;
};

#endif // CALLTRANSTRACTION_H
