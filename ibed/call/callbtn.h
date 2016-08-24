#ifndef CALLBTN_H
#define CALLBTN_H

#include <QObject>

class CallBtn : public QObject
{
    Q_OBJECT
public:
    CallBtn();

signals:
    void callPressed(void);
    void cancelPressed(void);
};

#endif // CALLBTN_H
