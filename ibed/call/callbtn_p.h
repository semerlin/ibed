#ifndef CALLBTN_P_H
#define CALLBTN_P_H

#include "call_global.h"
#include <QObject>
#include "boost/shared_ptr.hpp"

class QTimer;
class CallBtn;

class CALLSHARED_EXPORT CallBtnPrivate : public QObject
{
    Q_OBJECT
public:
    explicit CallBtnPrivate(CallBtn *parent);
    ~CallBtnPrivate();

public:
    int m_fd;
    boost::shared_ptr<QTimer> m_timer;

private slots:
    /**
     * @brief time interval button monitor
     */
    void onMonitorKeys(void);

private:
    CallBtn *const q_ptr;
    Q_DECLARE_PUBLIC(CallBtn)
};

#endif // CALLBTN_P

