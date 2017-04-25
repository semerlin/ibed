#ifndef CALLMANAGE_H
#define CALLMANAGE_H

#include <QObject>

class CallManagePrivate;

class CallManage : public QObject
{
    Q_OBJECT

public:
    CallManage();
    ~CallManage();

public:
    /**
     * @brief init call manage module
     * @return
     */
    bool init(void);

    /**
     * @brief register this device to sip server
     */
    void regToServer(void);

public slots:
    /**
     * @brief call out request handler
     */
    void onCallOutRequest(void);

    /**
     * @brief call terminate handler
     */
    void onTerminate(void);

signals:
    //call status signals
    void callOutConnecting(void);
    void callInConnecting(void);
    void callConnected(void);
    void callTerminate(void);

private:
    CallManagePrivate *const d_ptr;
    Q_DECLARE_PRIVATE(CallManage)
    Q_DISABLE_COPY(CallManage)

};

#endif // CALLMANGE_H
