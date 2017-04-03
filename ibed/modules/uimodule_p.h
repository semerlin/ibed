#ifndef UIMODULE_P_H
#define UIMODULE_P_H

#include "modules_global.h"
#include <QObject>

class MainWidget;
class StandbyWidget;
class CallWidget;
class ProgressDialog;
class NumIPMethod;
class QTimer;
class UiModule;

class MODULESSHARED_EXPORT UiModulePrivate : public QObject
{
    Q_OBJECT
public:
    explicit UiModulePrivate(UiModule *parent);
    ~UiModulePrivate();

public:
    /**
     * @brief init ui module
     */
    void init();

    /**
     * @brief deinit ui module
     */
    void deinit();

public:
    MainWidget *m_mainWidget;
    StandbyWidget *m_standbyWidget;
    CallWidget *m_callWidget;
    ProgressDialog *m_progressDialog;
#ifdef TARGET_IMX
    NumIPMethod *m_method;
#endif
    QTimer *m_standByTimer;
    int m_standByCount;

private slots:
    void onStandbyTimeout();
    void onBedCtrlPressed(void);
    void onBedCtrlReleased(void);

private:
    UiModule * const q_ptr;
    Q_DECLARE_PUBLIC(UiModule);
};


#endif // UIMODULE_P
