#ifndef NUMIPMETHOD_H
#define NUMIPMETHOD_H

#include <QWSInputMethod>

class NumPanel;

class NumIPMethod : public QWSInputMethod
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

#endif // NUMIPMETHOD_H
