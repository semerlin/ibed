#ifndef CALLBTN_H
#define CALLBTN_H

#include <QObject>
#include "call_global.h"
class QTimer;

class CALLSHARED_EXPORT CallBtn : public QObject
{
    Q_OBJECT
public:
    CallBtn();
    ~CallBtn();

public:
    bool init();

signals:
    void callPressed(void);
    void cancelPressed(void);

private slots:
    void onMonitorKeys(void);

private:
    int m_fd;
    QTimer *m_timer;
};

#endif // CALLBTN_H
