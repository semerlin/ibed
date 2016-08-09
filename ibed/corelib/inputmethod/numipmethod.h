#ifndef NUMIPMETHOD_H
#define NUMIPMETHOD_H

#ifdef TARGET_IMX
#include "inputmethod_global.h"
#include <QWSInputMethod>

class NumPanel;

class INPUTMETHODSHARED_EXPORT NumIPMethod : public QWSInputMethod
{
    Q_OBJECT
public:
    NumIPMethod();

public slots:
    void processKey(int key);

private:
    void processSpecial(int id);

private:
    NumPanel *m_panel;
    QString m_content;
};
#endif

#endif // NUMIPMETHOD_H
