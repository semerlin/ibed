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
    NumIPMethod(QWidget *parent = 0);
    ~NumIPMethod();

public:
    void updateHandler(int type);

public slots:
    void move(int x, int y);
    void resize(int width, int height);
    void setGeometry(int x, int y, int w, int h);
    void processKey(int key);

private:
    void processSpecial(int id);

private:
    NumPanel *m_panel;
};
#endif

#endif // NUMIPMETHOD_H
