#ifndef CALLBTN_H
#define CALLBTN_H

#include <QObject>
#include "call_global.h"
class QTimer;

class CallBtnPrivate;

class CALLSHARED_EXPORT CallBtn : public QObject
{
    Q_OBJECT
public:
    CallBtn();
    ~CallBtn();

public:
    /**
     * @brief init call button monitor
     * @return
     */
    bool init();

signals:
    /**
     * @brief this signal is emitted as soon as button pressed
     */
    void callPressed(void);

    /**
     * @brief this signal is emitted as soon as button released
     */
    void cancelPressed(void);

private:
    CallBtnPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(CallBtn)
    Q_DISABLE_COPY(CallBtn)
};

#endif // CALLBTN_H
